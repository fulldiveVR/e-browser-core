#include "brave/components/aiwize_llm/pref_registry.h"
#include "brave/components/aiwize_llm/pref_names.h"
#include "components/prefs/pref_registry_simple.h"

namespace aiwize_llm {

void RegisterAIWizeLLMPrefs(PrefRegistrySimple* registry) {
  registry->RegisterBooleanPref(prefs::kUseGPU, true);
}

}  // namespace aiwize_llm
