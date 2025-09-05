/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */

#ifndef BRAVE_BROWSER_UI_WEBUI_AI_COMBINER_CHAT_AIWIZE_AI_COMBINER_CHAT_UI_H_
#define BRAVE_BROWSER_UI_WEBUI_AI_COMBINER_CHAT_AIWIZE_AI_COMBINER_CHAT_UI_H_

#include <string>
#include <memory>

#include "content/public/browser/web_ui_controller.h"
#include "content/public/browser/webui_config.h"

class AICombinerChatUI : public content::WebUIController {
 public:
  explicit AICombinerChatUI(content::WebUI* web_ui);
  ~AICombinerChatUI() override;

  WEB_UI_CONTROLLER_TYPE_DECL();
};

#endif  // BRAVE_BROWSER_UI_WEBUI_AI_COMBINER_CHAT_AIWIZE_AI_COMBINER_CHAT_UI_H_
