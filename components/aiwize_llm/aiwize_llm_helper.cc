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
#include "base/process/kill.h"
#include "content/public/common/result_codes.h"
#include "base/time/time.h"

namespace aiwize_llm {

#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)
#else
const wchar_t kOllamaExe[] = L"ollama.exe";
#endif  // BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)

AIWizeLLMHelper* AIWizeLLMHelper::GetInstance() {
  static base::NoDestructor<AIWizeLLMHelper> instance;
  return instance.get();
}

AIWizeLLMHelper::AIWizeLLMHelper() {
  process_ = std::nullopt;
}

AIWizeLLMHelper::~AIWizeLLMHelper() = default;

void AIWizeLLMHelper::StartService() {
  if(process_) {
    return;
  }

  base::FilePath exe_dir;
  base::PathService::Get(base::DIR_ASSETS, &exe_dir);
#if BUILDFLAG(IS_LINUX)
  base::CommandLine command_line(exe_dir.Append(kAIWizeLLMExecutableLinux));
#elif BUILDFLAG(IS_MAC)
  base::CommandLine command_line(exe_dir.Append(kAIWizeLLMExecutableMac));
#else
  base::CommandLine command_line(exe_dir.Append(kAIWizeLLMExecutable));
#endif
  command_line.AppendArg("server");
  command_line.AppendArg("start");
  command_line.AppendArg("--init");
  command_line.AppendArg("--gpu");
  command_line.AppendArg("--port");
  command_line.AppendArg("22002");
  command_line.AppendArg("-O");
  command_line.AppendArg(exe_dir.AsUTF8Unsafe());

  LOG(ERROR) << "StartService, command_line: " << command_line.GetCommandLineString();

  base::LaunchOptions options;
#if BUILDFLAG(IS_LINUX)
  options.kill_on_parent_death = true;
#endif
#if BUILDFLAG(IS_WIN)
  options.start_hidden = true;
#endif
  process_ = brave::ProcessLauncher::ExecuteProcess(command_line, options);
}

void AIWizeLLMHelper::StopService() {
  if(process_) {
      process_->Terminate(0, true);
  }
  process_ = std::nullopt;
#if BUILDFLAG(IS_WIN)
  base::CleanupProcesses(kOllamaExe, base::TimeDelta(), content::RESULT_CODE_NORMAL_EXIT, nullptr);
#endif  // BUILDFLAG(IS_WIN)
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
#if BUILDFLAG(IS_LINUX)
  base::CommandLine command_line(exe_dir.Append(kAIWizeLLMExecutableLinux));
#elif BUILDFLAG(IS_MAC)
  base::CommandLine command_line(exe_dir.Append(kAIWizeLLMExecutableMac));
#else
  base::CommandLine command_line(exe_dir.Append(kAIWizeLLMExecutable));
#endif
  auto wide = command_line.GetCommandLineString();
  std::string str( wide.begin(), wide.end() );
  return str;
}


}  // namespace aiwize_llm
