/* Copyright (c) 2024 The AI Wize Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/webui/aiwize_applications_page_ui.h"

#include <memory>

#include "brave/browser/ui/webui/brave_webui_source.h"
#include "brave/components/aiwize_applications/browser/resources/grit/aiwize_applications_generated_map.h"
#include "chrome/browser/apps/app_service/app_icon/app_icon_factory.h"
#include "chrome/browser/favicon/favicon_service_factory.h"
#include "chrome/browser/image_fetcher/image_fetcher_service_factory.h"
#include "components/favicon/core/favicon_service.h"
#include "components/image_fetcher/core/image_fetcher.h"
#include "components/image_fetcher/core/image_fetcher_service.h"
#include "components/search_engines/template_url.h"
#include "ui/gfx/image/image.h"
#include "ui/gfx/image/image_skia.h"
#include "ui/gfx/image/image_skia_operations.h"
#include "base/base64.h"
#include "base/strings/utf_string_conversions.h"
#include "components/grit/brave_components_resources.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_data_source.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "content/public/common/bindings_policy.h"
#include "brave/components/constants/webui_url_constants.h"
#include "brave/components/webui/webui_resources.h"
#include "brave/components/sidebar/browser/sidebar_item.h"
#include "brave/components/sidebar/browser/sidebar_service.h"
#include "brave/browser/ui/sidebar/sidebar_service_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_key.h"

namespace {

constexpr char kImageFetcherUmaClientName[] = "AIWizeApplicationsFavicon";

constexpr net::NetworkTrafficAnnotationTag kAIWizeApplicationsFaviconTrafficAnnotation =
    net::DefineNetworkTrafficAnnotation("aiwize_applications", R"(
      semantics {
        sender: "Sidebar"
        description:
          "Fetches favicon for web type sidebar item"
        trigger:
          "When web type sidebar item is added to sidebar"
        data: "URL of the favicon image to be fetched."
        destination: WEBSITE
      }
      policy {
        cookies_allowed: NO
        setting: "Disabled when the user disabled sidebar."
      })");

}  // namespace


class AIWizeApplicationsMessageHandler
    : public content::WebUIMessageHandler, 
      public sidebar::SidebarService::Observer {
 private:
  raw_ptr<Profile> profile_ = nullptr;
  raw_ptr<sidebar::SidebarService> sidebar_service_ = nullptr;
  std::unique_ptr<base::CancelableTaskTracker> task_tracker_;

 public:
  AIWizeApplicationsMessageHandler() : task_tracker_(new base::CancelableTaskTracker{}) {
  }
  ~AIWizeApplicationsMessageHandler() override {
    if(sidebar_service_) {
      sidebar_service_->RemoveObserver(this);
    }

    profile_ = nullptr;
    sidebar_service_ = nullptr;
  }

 private:
  // WebUIMessageHandler implementation.
  void RegisterMessages() override {
    profile_ = Profile::FromWebUI(web_ui());
    sidebar_service_ = sidebar::SidebarServiceFactory::GetForProfile(profile_);
    sidebar_service_->AddObserver(this);

    web_ui()->RegisterMessageCallback(
        "aiwize_applications.addItem",
        base::BindRepeating(&AIWizeApplicationsMessageHandler::AddItem,
                            base::Unretained(this)));
    web_ui()->RegisterMessageCallback(
        "aiwize_applications.removeItem",
        base::BindRepeating(&AIWizeApplicationsMessageHandler::RemoveItem,
                            base::Unretained(this)));
    web_ui()->RegisterMessageCallback(
        "aiwize_applications.getItems",
        base::BindRepeating(&AIWizeApplicationsMessageHandler::GetItems,
                            base::Unretained(this)));
    web_ui()->RegisterMessageCallback(
        "aiwize_applications.getFavIcon",
        base::BindRepeating(&AIWizeApplicationsMessageHandler::GetFavIcon,
                            base::Unretained(this)));
  }
  
  void OnItemAdded(const sidebar::SidebarItem& item, size_t index) override {
    AllowJavascript();
    const auto url = item.url.spec();
    if(url.length() > 0) {
      CallJavascriptFunction("aiwize_applications.onItemAdded", base::Value(url));
    }
  }

  void OnItemRemoved(const sidebar::SidebarItem& item, size_t index) override {
    AllowJavascript();
    const auto url = item.url.spec();
    if(url.length() > 0) {
      CallJavascriptFunction("aiwize_applications.onItemRemoved", base::Value(url));
    }
  }

  int FindItem(const GURL link) {
    const auto items = sidebar_service_->items();

    int count = items.size();
    for (int i = 0; i < count; ++i) {
        if(items[i].url.spec() == link.spec()) {
            return i;
        }
    }

    return -1;
  }  

  void AddItem(const base::Value::List& args) {
    CHECK_EQ(2U, args.size());
    auto url = args[0].GetString();
    auto title = args[1].GetString();
    auto gurl = GURL(url);
    int index = FindItem(gurl);
    if(index == -1) {
        sidebar_service_->AddItem(sidebar::SidebarItem::Create(gurl, base::UTF8ToUTF16(title), sidebar::SidebarItem::Type::kTypeWeb,
                            sidebar::SidebarItem::BuiltInItemType::kNone, false));
    }
  }

  void RemoveItem(const base::Value::List& args) {
    CHECK_EQ(1U, args.size());
    auto url = args[0].GetString();
    auto gurl = GURL(url);
    int index = FindItem(gurl);
    if(index >= 0) {
        sidebar_service_->RemoveItemAt(index);
    }
  }

  void GetItems(const base::Value::List& args) {
    DCHECK_EQ(args.size(), 0U);
    AllowJavascript();

    const auto visible_items = sidebar_service_->items();

    auto items = base::Value::List();

    for (const auto& item : visible_items) {
      const auto url = item.url.spec();
      if(url.length() > 0) {
        items.Append(url);
      }
    }

    CallJavascriptFunction("aiwize_applications.onGetItems", items);
  }

  void GetFavIcon(const base::Value::List& args) {
    CHECK_EQ(1U, args.size());
    auto url = args[0].GetString();
    FetchFavicon(url);
  }

  void FetchFavicon(const std::string url) {
  // Use favicon as a web type icon's image.
    auto* favicon_service = FaviconServiceFactory::GetForProfile(
        profile_, ServiceAccessType::EXPLICIT_ACCESS);
    // nullptr in unit test.
    if (!favicon_service)
      return;
    favicon_service->GetRawFaviconForPageURL(
      GURL(url), {favicon_base::IconType::kFavicon}, 0 /*largest*/, false,
      base::BindRepeating(&AIWizeApplicationsMessageHandler::OnGetLocalFaviconImage,
                          base::Unretained(this), url),
      task_tracker_.get());
   }

  void OnGetLocalFaviconImage(
      const std::string& url,
      const favicon_base::FaviconRawBitmapResult& bitmap_result) {

    if (bitmap_result.is_valid()) {
        const gfx::ImageSkia skiaImage = gfx::Image::CreateFrom1xPNGBytes(bitmap_result.bitmap_data).AsImageSkia();
        SendSkiaImage(url, skiaImage);
    } else {
      FetchFaviconFromNetwork(url);
    }
  }

  void FetchFaviconFromNetwork(const std::string& url) {
    auto* service =
        ImageFetcherServiceFactory::GetForKey(profile_->GetProfileKey());
    DCHECK(service);
    auto* fetcher = service->GetImageFetcher(
        image_fetcher::ImageFetcherConfig::kDiskCacheOnly);
    image_fetcher::ImageFetcherParams params(kAIWizeApplicationsFaviconTrafficAnnotation,
                                            kImageFetcherUmaClientName);

    fetcher->FetchImage(
        TemplateURL::GenerateFaviconURL(GURL(url)),
        base::BindOnce(&AIWizeApplicationsMessageHandler::OnGetFaviconImageFromNetwork,
                      base::Unretained(this), url),
        params);
  }

  void OnGetFaviconImageFromNetwork(
      const std::string& url,
      const gfx::Image& image,
      const image_fetcher::RequestMetadata& request_metadata) {
    if (!image.IsEmpty()) {
      const gfx::ImageSkia skiaImage = image.AsImageSkia();
      SendSkiaImage(url, skiaImage);
    }
  }

  void SendSkiaImage(
    const std::string& url,
    const gfx::ImageSkia& image) {
    
    std::vector<uint8_t> encoded_image = apps::EncodeImageToPngBytes(image, 1.0);

    AllowJavascript();

    
    // base::Value::BlobStorage data = base::Value::BlobStorage(encoded_image.begin(), encoded_image.end());
    base::Value data = base::Value("data:image/png;base64," + base::Base64Encode(encoded_image));

    CallJavascriptFunction("aiwize_applications.onFavIcon", url, data);
  }

};

AIWizeApplicationsUI::AIWizeApplicationsUI(content::WebUI* web_ui)
    : WebUIController(web_ui) {
  web_ui->SetBindings(
      content::BindingsPolicySet({content::BindingsPolicyValue::kWebUi}));
  web_ui->AddMessageHandler(
      std::make_unique<AIWizeApplicationsMessageHandler>());

  auto* source = CreateAndAddWebUIDataSource(web_ui, 
                              kAIWizeApplicationsPageHost, 
                              kAiwizeApplicationsGenerated,
                              IDR_AIWIZE_APPLICATIONS_HTML,
                              true /*disable_trusted_types_csp*/);

  source->AddResourcePath("index.js", IDR_AIWIZE_APPLICATIONS_JS);
  source->AddResourcePath("index.css", IDR_AIWIZE_APPLICATIONS_CSS);
  source->AddResourcePath("favicon.ico", IDR_AIWIZE_APPLICATIONS_FAVICON);
  source->AddResourcePath("apps.js", IDR_AIWIZE_APPLICATIONS_DATA);
  source->AddResourcePath("materialdesignicons-webfont.ttf", IDR_AIWIZE_APPLICATIONS_FONT1);
  source->AddResourcePath("materialdesignicons-webfont.eot", IDR_AIWIZE_APPLICATIONS_FONT2);
  source->AddResourcePath("materialdesignicons-webfont.woff2", IDR_AIWIZE_APPLICATIONS_FONT3);
  source->AddResourcePath("materialdesignicons-webfont.woff", IDR_AIWIZE_APPLICATIONS_FONT4);
  source->AddString("searchHint", "Search for apps!");
  source->AddString("emptyLabel", "Nothing is found");

  
  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::StyleSrc,
      std::string("style-src chrome://resources chrome://applications aiwize://applications 'unsafe-inline';"));
  
  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ImgSrc,
      std::string("img-src 'self' data: aiwize: chrome://applications chrome://resources aiwize://resources 'unsafe-inline';"));

  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ScriptSrc,
      std::string("script-src 'self' chrome://resources chrome://applications aiwize://applications 'unsafe-inline';"));
}

AIWizeApplicationsUI::~AIWizeApplicationsUI() = default;

WEB_UI_CONTROLLER_TYPE_IMPL(AIWizeApplicationsUI)
