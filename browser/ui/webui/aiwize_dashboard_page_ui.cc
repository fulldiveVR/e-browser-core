/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */

#include "brave/browser/ui/webui/aiwize_dashboard_page_ui.h"

#include <memory>


#include "brave/browser/ui/webui/brave_webui_source.h"
#include "brave/components/aiwize_dashboard/browser/resources/grit/aiwize_dashboard_generated_map.h"

#include "components/grit/brave_components_resources.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_data_source.h"
#include "content/public/common/bindings_policy.h"
#include "brave/components/constants/webui_url_constants.h"
#include "brave/components/webui/webui_resources.h"

AIWizeDashboardUI::AIWizeDashboardUI(content::WebUI* web_ui)
    : WebUIController(web_ui) {
  web_ui->SetBindings(content::BindingsPolicySet());

  auto* source = CreateAndAddWebUIDataSource(web_ui, 
                              kAIWizeDashboardPageHost, 
                              kAiwizeDashboardGenerated,
                              IDR_AIWIZE_DASHBOARD_HTML,
                              true /*disable_trusted_types_csp*/);

  source->AddResourcePath("index.js", IDR_AIWIZE_DASHBOARD_JS);
  source->AddResourcePath("index.css", IDR_AIWIZE_DASHBOARD_CSS);
  source->AddResourcePath("favicon.ico", IDR_AIWIZE_DASHBOARD_FAVICON);
  source->AddResourcePath("materialdesignicons-webfont.ttf", IDR_AIWIZE_DASHBOARD_FONT1);
  source->AddResourcePath("materialdesignicons-webfont.eot", IDR_AIWIZE_DASHBOARD_FONT2);
  source->AddResourcePath("materialdesignicons-webfont.woff2", IDR_AIWIZE_DASHBOARD_FONT3);
  source->AddResourcePath("materialdesignicons-webfont.woff", IDR_AIWIZE_DASHBOARD_FONT4);

  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::StyleSrc,
      std::string("style-src chrome://resources chrome://settings chrome://dashboard aiwize://dashboard 'unsafe-inline';"));
  
  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ConnectSrc,
      std::string("connect-src http: chrome: aiwize: http://localhost:* ws://localhost:*;"));

  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ScriptSrc,
      std::string("script-src 'self' chrome://resources chrome://settings chrome://dashboard aiwize://dashboard 'unsafe-inline';"));
}

AIWizeDashboardUI::~AIWizeDashboardUI() = default;

WEB_UI_CONTROLLER_TYPE_IMPL(AIWizeDashboardUI)
