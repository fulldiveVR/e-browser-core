/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */

#ifndef BRAVE_BROWSER_UI_WEBUI_AIWIZE_DASHBOARD_AIWIZE_DASHBOARD_UI_H_
#define BRAVE_BROWSER_UI_WEBUI_AIWIZE_DASHBOARD_AIWIZE_DASHBOARD_UI_H_

#include <string>
#include <memory>

#include "content/public/browser/web_ui_controller.h"
#include "content/public/browser/webui_config.h"

class AIWizeDashboardUI : public content::WebUIController {
 public:
  explicit AIWizeDashboardUI(content::WebUI* web_ui);
  ~AIWizeDashboardUI() override;

  WEB_UI_CONTROLLER_TYPE_DECL();
};

#endif  // BRAVE_BROWSER_UI_WEBUI_AIWIZE_DASHBOARD_AIWIZE_DASHBOARD_UI_H_
