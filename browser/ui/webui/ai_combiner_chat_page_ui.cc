/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */

#include "brave/browser/ui/webui/ai_combiner_chat_page_ui.h"

#include <memory>

#include "base/base64.h"
#include "base/functional/bind.h"
#include "base/strings/utf_string_conversions.h"
#include "base/uuid.h"
#include "brave/browser/ui/webui/aiwize_data_source.h"
#include "brave/browser/ui/webui/brave_webui_source.h"
#include "brave/components/ai_combiner/content/browser/screenshotter.h"
#include "brave/components/ai_combiner_chat/browser/resources/grit/ai_combiner_chat_generated_map.h"
#include "brave/components/constants/webui_url_constants.h"
#include "brave/components/webui/webui_resources.h"
#include "chrome/browser/offline_pages/offline_page_utils.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "components/grit/brave_components_resources.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_data_source.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "content/public/common/bindings_policy.h"
#include "content/public/common/mhtml_generation_params.h"
#include "net/base/filename_util.h"

#if BUILDFLAG(IS_WIN)
#include <codecvt> // For std::codecvt_utf8_utf16
#include <locale>  // For std::wstring_convert

std::wstring convert_utf8_to_utf16(const std::string& utf8_string) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    return base::AsWString(converter.from_bytes(utf8_string));
}
#endif

class AICombinerChatMessageHandler : public content::WebUIMessageHandler {
 public:
  AICombinerChatMessageHandler(Profile* profile) : profile_(profile) {}
  ~AICombinerChatMessageHandler() override {}

 private:
  std::unique_ptr<ai_combiner::Screenshotter> screenshotter_;

 private:
  // WebUIMessageHandler implementation.
  void RegisterMessages() override {
    web_ui()->RegisterMessageCallback(
        "aiwize_applications.openLink",
        base::BindRepeating(&AICombinerChatMessageHandler::openLink,
                            base::Unretained(this)));
    web_ui()->RegisterMessageCallback(
        "aiwize_applications.getPageContent",
        base::BindRepeating(&AICombinerChatMessageHandler::getPageContent,
                            base::Unretained(this)));
    web_ui()->RegisterMessageCallback(
        "aiwize_applications.getPageInfo",
        base::BindRepeating(&AICombinerChatMessageHandler::getPageInfo,
                            base::Unretained(this)));
    web_ui()->RegisterMessageCallback(
        "aiwize_applications.getPageScreenshots",
        base::BindRepeating(&AICombinerChatMessageHandler::getPageScreenshots,
                            base::Unretained(this)));
  }
  content::WebContents* GetActiveWebContents() {
    Browser* browser = chrome::FindLastActive();
    if (browser) {
      return browser->tab_strip_model()->GetActiveWebContents();
    }
    return nullptr;
  }

  void getPageInfo(const base::Value::List& args) {
    LOG(ERROR) << "getPageInfo called";
    content::WebContents* active_web_contents = GetActiveWebContents();

    if (active_web_contents) {
      const auto url = active_web_contents->GetURL().spec();
      std::u16string title = active_web_contents->GetTitle();
      AllowJavascript();
      web_ui()->CallJavascriptFunctionUnsafe(
          "aiwize_applications.onPageInfoReceived", base::Value(url),
          base::Value(title));
    }
  }

  void getPageScreenshots(const base::Value::List& args) {
    bool capture_visible_bounds = true;
    if (args.size() > 0) {
      capture_visible_bounds = args[0].GetBool();
    }

    screenshotter_ =
        std::make_unique<ai_combiner::Screenshotter>(capture_visible_bounds);
    screenshotter_->CaptureScreenshots(
        GetActiveWebContents(),
        base::BindOnce(&AICombinerChatMessageHandler::OnScreenshotsCaptured,
                       base::Unretained(this)));
  }

  void OnScreenshotsCaptured(
      base::expected<std::vector<std::vector<uint8_t>>, std::string> result) {
    base::Value::List screenshots;
    if (result.has_value()) {
      for (auto& screenshot : result.value()) {
        screenshots.Append(base::Value(base::Base64Encode(screenshot)));
      }
    } else {
      LOG(ERROR) << result.error();
    }
    AllowJavascript();
    web_ui()->CallJavascriptFunctionUnsafe(
        "aiwize_applications.onPageScreenshotsReceived", screenshots);
  }

  void getPageContent(const base::Value::List& args) {
    content::WebContents* active_web_contents = GetActiveWebContents();

    if (active_web_contents) {
      base::FilePath temp_dir_path;
      // Intentionally using base::GetTempDir to reuse same directory between
      // launches.
      if (!base::GetTempDir(&temp_dir_path) || temp_dir_path.empty()) {
        AllowJavascript();
        web_ui()->CallJavascriptFunctionUnsafe(
            "aiwize_applications.onPageContentReceived", base::Value(false),
            base::Value("Unable to get temporary directory"));
        return;
      }



#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)
      base::FilePath file_path(
          temp_dir_path
              .Append(base::Uuid::GenerateRandomV4().AsLowercaseString())
              .AddExtension(".mhtml"));
#else
      base::FilePath file_path(
          temp_dir_path
              .Append(convert_utf8_to_utf16(base::Uuid::GenerateRandomV4().AsLowercaseString()))
              .AddExtension(L".mhtml"));
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)


      content::MHTMLGenerationParams params(file_path);
      params.use_binary_encoding = false;
      params.remove_popup_overlay = true;

      active_web_contents->GenerateMHTMLWithResult(
          params, base::BindOnce(&AICombinerChatMessageHandler::OnTextReceived,
                                 base::Unretained(this), std::move(file_path)));
    }
  }
  void OnTextReceived(base::FilePath file_path,
                      const content::MHTMLGenerationResult& result) {
    AllowJavascript();
    bool success = false;
    std::string content = "";
    if (result.file_size < 0) {
      content = "Failed to generate MHTML";
    } else {
      if (base::ReadFileToString(file_path, &content)) {
        success = true;
      } else {
        content = "Failed to read MHTML file";
      }
      base::DeleteFile(file_path);
    }
    web_ui()->CallJavascriptFunctionUnsafe(
        "aiwize_applications.onPageContentReceived", base::Value(success),
        base::Value(content));
  }

  void openLink(const base::Value::List& args) {
    DCHECK(profile_);
    std::string link = args[0].GetString();
    auto window_open_disposition = WindowOpenDisposition::CURRENT_TAB;
    if (args.size() > 1) {
      if (args.size() > 1 && args[1] == "blank") {
        window_open_disposition = WindowOpenDisposition::NEW_FOREGROUND_TAB;
      }
      window_open_disposition = WindowOpenDisposition::CURRENT_TAB;
    }
    Browser* browser = chrome::FindBrowserWithProfile(profile_);
    if (browser) {
      content::OpenURLParams open_params(
          GURL(link), content::Referrer(), window_open_disposition,
          ui::PAGE_TRANSITION_AUTO_TOPLEVEL, false);
      browser->OpenURL(open_params, /*navigation_handle_callback=*/{});
    }
  }

 private:
  raw_ptr<Profile> profile_ = nullptr;
};

AICombinerChatUI::AICombinerChatUI(content::WebUI* web_ui)
    : WebUIController(web_ui) {
  auto* profile = Profile::FromWebUI(web_ui);
  web_ui->SetBindings(
      content::BindingsPolicySet({content::BindingsPolicyValue::kWebUi}));
  web_ui->AddMessageHandler(
      std::make_unique<AICombinerChatMessageHandler>(profile));

  auto* source = CreateAndAddWebUIDataSource(
      web_ui, kAiCombinerChatPageHost, kAiCombinerChatGenerated,
      IDR_AI_COMBINER_CHAT_HTML, true /*disable_trusted_types_csp*/);

  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::StyleSrc,
      std::string("style-src chrome://resources chrome://settings "
                  "chrome://ai-combiner-chat aiwize://ai-combiner-chat "
                  "http://localhost:* 'unsafe-inline';"));

  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ConnectSrc,
      std::string("connect-src http: chrome: aiwize: http://localhost:* "
                  "ws://localhost:*;"));

  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ScriptSrc,
      std::string("script-src 'self' chrome://resources chrome://settings "
                  "chrome://ai-combiner-chat aiwize://ai-combiner-chat "
                  "http://localhost:* 'unsafe-inline';"));

  content::URLDataSource::Add(profile,
                              std::make_unique<aiwize::AIWizeDataSource>(
                                  profile->GetURLLoaderFactory()));
}

AICombinerChatUI::~AICombinerChatUI() = default;

WEB_UI_CONTROLLER_TYPE_IMPL(AICombinerChatUI)
