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
  base::PathService::Get(base::DIR_ASSETS, &exe_dir);
  base::CommandLine command_line(exe_dir.Append(kAIWizeLLMExecutable));
  command_line.AppendArg("server");
  command_line.AppendArg("start");
  command_line.AppendArg("--init");
  command_line.AppendArg("--port");
  command_line.AppendArg("22002");

  LOG(ERROR) << "StartService, command_line: " << command_line.GetCommandLineString();

  base::LaunchOptions options;
#if BUILDFLAG(IS_LINUX)
  options.kill_on_parent_death = true;
#endif
#if BUILDFLAG(IS_WIN)
  options.start_hidden = true;
#endif
  process_ = brave::ProcessLauncher::ReadAppOutput(command_line, options);

  LOG(ERROR) << "StartService: " << kAIWizeLLMAPI;
}

void AIWizeLLMHelper::StopService() {
  LOG(ERROR) << "StopService";
  if(process_) {
      process_->Terminate(0, true);
  }
  process_ = std::nullopt;
}

std::string AIWizeLLMHelper::GetHostLLM() {
  return kAIWizeLLMAPI;
}

bool AIWizeLLMHelper::IsInProcess() {
  return process_ != std::nullopt;
}

std::string AIWizeLLMHelper::GetInfoLLM() {
  base::FilePath exe_dir;
  base::PathService::Get(base::DIR_ASSETS, &exe_dir);
  base::CommandLine command_line(exe_dir.Append(kAIWizeLLMExecutable));
  std::wstring wide = command_line.GetCommandLineString();
  std::string str( wide.begin(), wide.end() );
  return str;
}


}  // namespace aiwize_llm
