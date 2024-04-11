/* Copyright (c) 2024 The AI WIze Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/webui/settings/aiwize_llm_settings_handler.h"

#include <algorithm>
#include <utility>
#include <vector>

#include "base/containers/contains.h"
#include "brave/browser/brave_browser_process.h"
#include "brave/browser/misc_metrics/process_misc_metrics.h"
#include "brave/browser/ui/sidebar/sidebar_service_factory.h"
#include "brave/components/ai_chat/core/common/mojom/ai_chat.mojom.h"
#include "brave/components/ai_chat/core/common/pref_names.h"
#include "components/prefs/pref_service.h"
#include "brave/components/aiwize_llm/aiwize_llm_helper.h"

namespace settings {

AIWizeLLMSettingsHandler::AIWizeLLMSettingsHandler() = default;
AIWizeLLMSettingsHandler::~AIWizeLLMSettingsHandler() = default;

void AIWizeLLMSettingsHandler::RegisterMessages() {
  web_ui()->RegisterMessageCallback(
      "startAIWizeLLM",
      base::BindRepeating(&AIWizeLLMSettingsHandler::HandleStartAIWizeLLM,
                          base::Unretained(this)));
}


void AIWizeLLMSettingsHandler::OnJavascriptAllowed() {
}

void AIWizeLLMSettingsHandler::OnJavascriptDisallowed() {
}


void AIWizeLLMSettingsHandler::HandleStartAIWizeLLM(
    const base::Value::List& args) {
  aiwize_llm::AIWizeLLMHelper::GetInstance()->StopService();
  aiwize_llm::AIWizeLLMHelper::GetInstance()->StartService();
}

}  // namespace settings
