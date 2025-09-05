/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */

#ifndef BRAVE_COMPONENTS_AI_COMBINER_AI_COMBINER_CONSTANTS_H_
#define BRAVE_COMPONENTS_AI_COMBINER_AI_COMBINER_CONSTANTS_H_

#include "build/buildflag.h"

namespace ai_combiner {

inline constexpr wchar_t kAiCombinerExecutable[] = L"browser-api.exe";
inline constexpr char kAiCombinerExecutableMac[] = "browser-api-macos-arm";
inline constexpr char kAiCombinerExecutableLinux[] = "browser-api";
inline constexpr wchar_t kQdrantExecutable[] = L"qdrant-win.exe";
inline constexpr char kQdrantExecutableMac[] = "qdrant-macos";
inline constexpr char kQdrantExecutableLinux[] = "qdrant-linux";

inline constexpr char kAiCombinerAPI[] = "localhost:22003";
inline constexpr char kAiCombinerHost[] = "localhost";
inline constexpr char kAiCombinerPort[] = "22003";

}  // namespace ai_combiner

#endif  // BRAVE_COMPONENTS_AI_COMBINER_AI_COMBINER_CONSTANTS_H_
