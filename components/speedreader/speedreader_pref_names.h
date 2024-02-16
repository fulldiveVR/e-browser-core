/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_SPEEDREADER_SPEEDREADER_PREF_NAMES_H_
#define BRAVE_COMPONENTS_SPEEDREADER_SPEEDREADER_PREF_NAMES_H_

namespace speedreader {

// Is Speedreader currently enabled
// java_cpp_string.py doesn't work when the variable is constexpr
inline constexpr char kSpeedreaderPrefEnabled[] = "aiwize.speedreader.enabled";

// Set if Speedreader was enabled at least once
inline constexpr char kSpeedreaderPrefEverEnabled[] =
    "aiwize.speedreader.ever_enabled";

// Number of times the user has toggled Speedreader
inline constexpr char kSpeedreaderPrefToggleCount[] =
    "aiwize.speedreader.toggle_count";

// Number of times the "Enable Speedreader" button was shown automatically
inline constexpr char kSpeedreaderPrefPromptCount[] =
    "aiwize.speedreader.prompt_count";

// The theme selected by the user. If it has a default value then system theme
// should be used.
inline constexpr char kSpeedreaderPrefTheme[] = "aiwize.speedreader.theme";

inline constexpr char kSpeedreaderPrefFontSize[] =
    "aiwize.speedreader.font_size";

inline constexpr char kSpeedreaderPrefFontFamily[] =
    "aiwize.speedreader.font_family";

inline constexpr char kSpeedreaderPrefColumnWidth[] =
    "aiwize.speedreader.column_width";

inline constexpr char kSpeedreaderPrefTtsVoice[] =
    "aiwize.speedreader.tts_voice";

inline constexpr char kSpeedreaderPrefTtsSpeed[] =
    "aiwize.speedreader.tts_speed";

}  // namespace speedreader

#endif  // BRAVE_COMPONENTS_SPEEDREADER_SPEEDREADER_PREF_NAMES_H_
