/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */

#ifndef BRAVE_COMPONENTS_AI_COMBINER_AI_COMBINER_HELPER_H_
#define BRAVE_COMPONENTS_AI_COMBINER_AI_COMBINER_HELPER_H_

#include <optional>
#include <string>
#include "base/process/process.h"
#include "base/no_destructor.h"

namespace ai_combiner {

class AICombinerHelper {
 public:
  static AICombinerHelper* GetInstance();

 private:
  friend class base::NoDestructor<AICombinerHelper>;

  AICombinerHelper();
  ~AICombinerHelper();
  
 public:

  void StartService();
  void StopService();
  
  std::string GetHost();
  bool IsInProcess();

  private:
   std::optional<base::Process> process_;
};

}  // namespace ai_combiner

#endif  // BRAVE_COMPONENTS_AI_COMBINER_AI_COMBINER_HELPER_H_
