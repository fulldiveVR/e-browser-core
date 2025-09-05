/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */

#include "brave/components/ai_combiner/ai_combiner_helper.h"

#include "base/command_line.h"
#include "base/logging.h"
#include "base/no_destructor.h"
#include "base/path_service.h"
#include "base/process/kill.h"
#include "base/time/time.h"
#include "brave/base/process/process_launcher.h"
#include "brave/components/ai_combiner/ai_combiner_constants.h"
#include "content/public/common/result_codes.h"

namespace ai_combiner {

AICombinerHelper* AICombinerHelper::GetInstance() {
  static base::NoDestructor<AICombinerHelper> instance;
  return instance.get();
}

AICombinerHelper::AICombinerHelper() {
  process_ = std::nullopt;
}

AICombinerHelper::~AICombinerHelper() = default;

void AICombinerHelper::StartService() {
  if (process_) {
    return;
  }

  base::FilePath exe_dir;
  base::PathService::Get(base::DIR_ASSETS, &exe_dir);
#if BUILDFLAG(IS_LINUX)
  base::CommandLine command_line(exe_dir.Append(kAiCombinerExecutableLinux));
  base::FilePath qdrant_path = exe_dir.Append(kQdrantExecutableLinux);
#elif BUILDFLAG(IS_MAC)
  base::CommandLine command_line(exe_dir.Append(kAiCombinerExecutableMac));
  base::FilePath qdrant_path = exe_dir.Append(kQdrantExecutableMac);
#else
  base::CommandLine command_line(exe_dir.Append(kAiCombinerExecutable));
  base::FilePath qdrant_path = exe_dir.Append(kQdrantExecutable);
#endif
  command_line.AppendArg("--port");
  command_line.AppendArg("22003");
  command_line.AppendArg("--base-domain");
  command_line.AppendArg("aiwize.com");
  command_line.AppendArg("--verbose");
  command_line.AppendArg("--qdrant-bin-path");
  command_line.AppendArg(qdrant_path.AsUTF8Unsafe());

  LOG(ERROR) << "StartService, command_line: "
             << command_line.GetCommandLineString();

  base::LaunchOptions options;
#if BUILDFLAG(IS_LINUX)
  options.kill_on_parent_death = true;
#endif
#if BUILDFLAG(IS_WIN)
  options.start_hidden = true;
#endif
  process_ = brave::ProcessLauncher::ExecuteProcess(command_line, options);
}

void AICombinerHelper::StopService() {
#if BUILDFLAG(IS_LINUX)
  // base::CommandLine command_line(exe_dir.Append(kAIWizeLLMExecutableLinux));
#elif BUILDFLAG(IS_MAC)
  base::CleanupProcesses(kAiCombinerExecutableMac, base::TimeDelta(),
                         content::RESULT_CODE_HUNG, nullptr);
  base::CleanupProcesses(kQdrantExecutableMac, base::TimeDelta(),
                         content::RESULT_CODE_HUNG, nullptr);
#elif BUILDFLAG(IS_WIN)
  base::CleanupProcesses(kAiCombinerExecutable, base::TimeDelta(),
                         content::RESULT_CODE_HUNG, nullptr);
#endif
  if (process_) {
    process_->Terminate(0, true);
  }
  process_ = std::nullopt;
}

std::string AICombinerHelper::GetHost() {
  return kAiCombinerAPI;
}

bool AICombinerHelper::IsInProcess() {
  return process_ != std::nullopt;
}

}  // namespace ai_combiner
