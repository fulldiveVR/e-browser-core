/* Copyright (c) 2019 The AI Wize Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_UI_WEBUI_AIWIZE_APPLICATIONS_AIWIZE_APPLICATIONS_UI_H_
#define BRAVE_BROWSER_UI_WEBUI_AIWIZE_APPLICATIONS_AIWIZE_APPLICATIONS_UI_H_

#include <string>
#include <memory>

#include "content/public/browser/web_ui_controller.h"
#include "content/public/browser/webui_config.h"

class AIWizeApplicationsUI : public content::WebUIController {
 public:
  explicit AIWizeApplicationsUI(content::WebUI* web_ui);
  ~AIWizeApplicationsUI() override;

  WEB_UI_CONTROLLER_TYPE_DECL();
};

#endif  // BRAVE_BROWSER_UI_WEBUI_AIWIZE_APPLICATIONS_AIWIZE_APPLICATIONS_UI_H_
