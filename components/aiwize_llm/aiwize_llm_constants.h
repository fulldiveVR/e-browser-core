
#ifndef BRAVE_COMPONENTS_AIWIZE_LLM_AIWIZE_LLM_CONSTANTS_H_
#define BRAVE_COMPONENTS_AIWIZE_LLM_AIWIZE_LLM_CONSTANTS_H_

#include "build/buildflag.h"

namespace aiwize_llm {

inline constexpr wchar_t kAIWizeLLMExecutable[] = L"aiwize-windows-amd64.exe";
inline constexpr char kAIWizeLLMExecutableMac[] = "aiwize-darwin";
inline constexpr char kOllamaLLMExecutableMac[] = "ollama-darwin";
inline constexpr char kOllamaLLamaLLMExecutableMac[] = "ollama_llama_server_darwin";
inline constexpr char kAIWizeLLMExecutableLinux[] = "aiwize-linux-amd64";

inline constexpr char kAIWizeLLMAPI[] = "localhost:22002";
inline constexpr char kAIWizeLLMInfo[] = "localhost:22002/_info";
inline constexpr char kAIWizeLLMHost[] = "localhost";
inline constexpr char kAIWizeLLMPort[] = "22002";
inline constexpr char kAIWizeLLMPath[] = "/v1/chat/completions";
inline constexpr char kAIChatModelPath[] = "/system/settings";
inline constexpr char kAIWizeLLMCustomModel[] = "::customModel::";


}  // namespace aiwize_llm

#endif  // BRAVE_COMPONENTS_AIWIZE_LLM_AIWIZE_LLM_CONSTANTS_H_
