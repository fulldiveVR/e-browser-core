/* Copyright (c) 2024 The AI Wize Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_UI_WEBUI_SETTINGS_BRAVE_SETTINGS_AIWIZE_LLM_HANDLER_H_
#define BRAVE_BROWSER_UI_WEBUI_SETTINGS_BRAVE_SETTINGS_AIWIZE_LLM_HANDLER_H_

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "chrome/browser/ui/webui/settings/settings_page_ui_handler.h"
#include "components/prefs/pref_change_registrar.h"

namespace settings {

class AIWizeLLMSettingsHandler : public settings::SettingsPageUIHandler {
 public:
  AIWizeLLMSettingsHandler();
  ~AIWizeLLMSettingsHandler() override;

  AIWizeLLMSettingsHandler(const AIWizeLLMSettingsHandler&) = delete;
  AIWizeLLMSettingsHandler& operator=(const AIWizeLLMSettingsHandler&) = delete;

 private:
  // SettingsPageUIHandler overrides:
  void RegisterMessages() override;
  void HandleStartAIWizeLLM(const base::Value::List& args);
  
  void OnJavascriptAllowed() override;
  void OnJavascriptDisallowed() override;

};

}  // namespace settings

#endif  // BRAVE_BROWSER_UI_WEBUI_SETTINGS_BRAVE_SETTINGS_AIWIZE_LLM_HANDLER_H_
