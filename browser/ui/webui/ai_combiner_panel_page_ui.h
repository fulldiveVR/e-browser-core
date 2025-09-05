/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */

#ifndef BRAVE_BROWSER_UI_WEBUI_AI_COMBINER_PANEL_AIWIZE_AI_COMBINER_PANEL_UI_H_
#define BRAVE_BROWSER_UI_WEBUI_AI_COMBINER_PANEL_AIWIZE_AI_COMBINER_PANEL_UI_H_

#include <memory>
#include <string>

#include "chrome/browser/ui/webui/top_chrome/top_chrome_web_ui_controller.h"
#include "chrome/browser/ui/webui/top_chrome/top_chrome_webui_config.h"
#include "content/public/browser/web_ui_controller.h"
#include "content/public/browser/webui_config.h"

class AICombinerPanelUI : public content::WebUIController {
 public:
  explicit AICombinerPanelUI(content::WebUI* web_ui);
  AICombinerPanelUI(const AICombinerPanelUI&) = delete;
  AICombinerPanelUI& operator=(const AICombinerPanelUI&) = delete;

  ~AICombinerPanelUI() override;

  static constexpr std::string_view GetWebUIName() { return "AICombinerPanel"; }

  void set_embedder(
      base::WeakPtr<TopChromeWebUIController::Embedder> embedder) {
    embedder_ = embedder;
  }

private:
  base::WeakPtr<TopChromeWebUIController::Embedder> embedder_;

  WEB_UI_CONTROLLER_TYPE_DECL();
};


class AICombinerPanelUIConfig : public DefaultTopChromeWebUIConfig<AICombinerPanelUI> {
 public:
  AICombinerPanelUIConfig();
  ~AICombinerPanelUIConfig() override = default;

  bool IsWebUIEnabled(content::BrowserContext* browser_context) override;
};


#endif  // BRAVE_BROWSER_UI_WEBUI_AI_COMBINER_PANEL_AIWIZE_AI_COMBINER_PANEL_UI_H_
