/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/aiwize_llm/aiwize_llm_helper.h"
#include "brave/components/aiwize_llm/aiwize_llm_constants.h"
#include "base/logging.h"
#include "base/command_line.h"
#include "brave/base/process/process_launcher.h"
#include "base/path_service.h"
#include "base/no_destructor.h"

namespace aiwize_llm {

AIWizeLLMHelper* AIWizeLLMHelper::GetInstance() {
  static base::NoDestructor<AIWizeLLMHelper> instance;
  return instance.get();
}

AIWizeLLMHelper::AIWizeLLMHelper() {
  LOG(ERROR) << "AIWizeLLMHelper(): " << kAIWizeLLMExecutable;
  process_ = std::nullopt;
}

AIWizeLLMHelper::~AIWizeLLMHelper() = default;

void AIWizeLLMHelper::StartService() {
  LOG(ERROR) << "AIWizeLLMHelper():StartService() ";

  if(process_) {
    return;
  }

  base::FilePath exe_dir;
  base::PathService::Get(base::DIR_EXE, &exe_dir);
  base::CommandLine command_line(exe_dir.Append(kAIWizeLLMExecutable));

  LOG(ERROR) << "StartService, command_line: " << command_line.GetCommandLineString();

  base::LaunchOptions options;
  process_ = brave::ProcessLauncher::ReadAppOutput(command_line, options, host_llm_);
  LOG(ERROR) << "StartService: " << host_llm_;
}

void AIWizeLLMHelper::StopService() {
  LOG(ERROR) << "StopService";
  if(process_){
      process_->Terminate(0, true);
  }
  process_ = std::nullopt;
}

std::optional<std::string> AIWizeLLMHelper::GetHostLLM(){
  if(process_ && host_llm_.length() > 0) {
    return host_llm_;
  }
  
  return std::nullopt;
}

}  // namespace aiwize_llm
