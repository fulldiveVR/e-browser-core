/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_AI_CHAT_CORE_COMMON_PREF_NAMES_H_
#define BRAVE_COMPONENTS_AI_CHAT_CORE_COMMON_PREF_NAMES_H_

class PrefRegistrySimple;
class PrefService;

namespace ai_chat::prefs {

inline constexpr char kLastAcceptedDisclaimer[] =
    "aiwize.ai_chat.last_accepted_disclaimer";
inline constexpr char kBraveChatAutocompleteProviderEnabled[] =
    "aiwize.ai_chat.autocomplete_provider_enabled";
inline constexpr char kBraveChatP3AChatCountWeeklyStorage[] =
    "aiwize.ai_chat.p3a_chat_count";
inline constexpr char kBraveChatP3APromptCountWeeklyStorage[] =
    "aiwize.ai_chat.p3a_prompt_count";
// Stores Leo Premium credentials that have already been fetched from the
// SKU SDK but were not used because the chat server was unavailable.
inline constexpr char kBraveChatPremiumCredentialCache[] =
    "aiwize.ai_chat.premium_credential_cache";
inline constexpr char kUserDismissedPremiumPrompt[] =
    "aiwize.ai_chat.user_dismissed_premium_prompt";
inline constexpr char kDefaultModelKey[] = "aiwize.ai_chat.default_model_key";
inline constexpr char kBraveChatP3AOmniboxOpenWeeklyStorage[] =
    "aiwize.ai_chat.p3a_omnibox_open";
inline constexpr char kBraveChatP3AOmniboxAutocompleteWeeklyStorage[] =
    "aiwize.ai_chat.p3a_omnibox_autocomplete";
inline constexpr char kBraveChatP3ALastPremiumCheck[] =
    "aiwize.ai_chat.p3a_last_premium_check";
inline constexpr char kBraveChatP3ALastPremiumStatus[] =
    "aiwize.ai_chat.p3a_last_premium_status";

void RegisterProfilePrefs(PrefRegistrySimple* registry);

void RegisterProfilePrefsForMigration(PrefRegistrySimple* registry);
void MigrateProfilePrefs(PrefService* profile_prefs);

void RegisterLocalStatePrefs(PrefRegistrySimple* registry);

}  // namespace ai_chat::prefs

#endif  // BRAVE_COMPONENTS_AI_CHAT_CORE_COMMON_PREF_NAMES_H_
