/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_AIWIZE_LLM_AIWIZE_LLM_HELPER_H_
#define BRAVE_COMPONENTS_AIWIZE_LLM_AIWIZE_LLM_HELPER_H_

#include <optional>
#include <string>
#include "base/process/process.h"
#include "base/no_destructor.h"

namespace aiwize_llm {

class AIWizeLLMHelper {
 public:
  static AIWizeLLMHelper* GetInstance();

 private:
  friend class base::NoDestructor<AIWizeLLMHelper>;

  AIWizeLLMHelper();
  ~AIWizeLLMHelper();
  
 public:

  void StartService();
  void StopService();
  
  std::string GetHostLLM();
  std::string GetInfoLLM();
  bool IsInProcess();

  private:
   std::optional<base::Process> process_;
};

}  // namespace aiwize_llm_helper

#endif  // BRAVE_COMPONENTS_AIWIZE_LLM_AIWIZE_LLM_HELPER_H_
