/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

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
