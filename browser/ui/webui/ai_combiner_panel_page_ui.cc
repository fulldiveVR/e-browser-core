/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */

#include "brave/browser/ui/webui/ai_combiner_panel_page_ui.h"

#include <memory>

#include "brave/browser/ui/webui/brave_webui_source.h"
#include "brave/components/ai_combiner_panel/browser/resources/grit/ai_combiner_panel_generated_map.h"
#include "brave/components/constants/webui_url_constants.h"
#include "brave/components/webui/webui_resources.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "components/grit/brave_components_resources.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_data_source.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "content/public/common/bindings_policy.h"
#include "content/public/common/url_constants.h"

class AICombinerPanelMessageHandler : public content::WebUIMessageHandler {
 public:
  AICombinerPanelMessageHandler(Profile* profile) : profile_(profile) {}
  ~AICombinerPanelMessageHandler() override {}

 private:
  // WebUIMessageHandler implementation.
  void RegisterMessages() override {
    web_ui()->RegisterMessageCallback(
        "aiwize_applications.openLink",
        base::BindRepeating(&AICombinerPanelMessageHandler::openLink,
                            base::Unretained(this)));
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

AICombinerPanelUI::AICombinerPanelUI(content::WebUI* web_ui)
    : WebUIController(web_ui) {
  web_ui->SetBindings(
      content::BindingsPolicySet({content::BindingsPolicyValue::kWebUi}));
  web_ui->AddMessageHandler(std::make_unique<AICombinerPanelMessageHandler>(
      Profile::FromWebUI(web_ui)));

  auto* source = CreateAndAddWebUIDataSource(
      web_ui, kAiCombinerPanelPageHost, kAiCombinerPanelGenerated,
      IDR_AI_COMBINER_PANEL_HTML, true /*disable_trusted_types_csp*/);

  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::StyleSrc,
      std::string("style-src chrome://resources chrome://settings "
                  "chrome://ai-combiner-panel aiwize://ai-combiner-panel "
                  "http://localhost:* "
                  "'unsafe-inline';"));

  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ConnectSrc,
      std::string("connect-src http: chrome: aiwize: http://localhost:* ws://localhost:*;"));

  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ScriptSrc,
      std::string("script-src 'self' chrome://resources chrome://settings "
                  "chrome://ai-combiner-panel aiwize://ai-combiner-panel "
                  "http://localhost:* "
                  "'unsafe-inline';"));
}

AICombinerPanelUI::~AICombinerPanelUI() = default;

bool AICombinerPanelUIConfig::IsWebUIEnabled(
    content::BrowserContext* browser_context) {
  return true;  // Enable AICombinerPanel for all browser contexts.
}

AICombinerPanelUIConfig::AICombinerPanelUIConfig()
    : DefaultTopChromeWebUIConfig(content::kChromeUIScheme,
                                  kAiCombinerPanelPageHost) {}

WEB_UI_CONTROLLER_TYPE_IMPL(AICombinerPanelUI)
