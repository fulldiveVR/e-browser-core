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
  void SetUseGPU(bool value);

  private:
   std::optional<base::Process> process_;
   bool use_gpu_;
};

}  // namespace aiwize_llm_helper

#endif  // BRAVE_COMPONENTS_AIWIZE_LLM_AIWIZE_LLM_HELPER_H_
