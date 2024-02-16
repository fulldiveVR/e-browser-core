/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_CHROMIUM_SRC_COMPONENTS_SEARCH_ENGINES_SEARCH_ENGINES_PREF_NAMES_H_
#define BRAVE_CHROMIUM_SRC_COMPONENTS_SEARCH_ENGINES_SEARCH_ENGINES_PREF_NAMES_H_

#include "src/components/search_engines/search_engines_pref_names.h"  // IWYU pragma: export

namespace prefs {

inline constexpr char kDefaultSearchProviderByExtension[] =
    "aiwize.default_search_provider_by_extension";
inline constexpr char kAddOpenSearchEngines[] =
    "aiwize.other_search_engines_enabled";
inline constexpr char kBraveDefaultSearchVersion[] =
    "aiwize.search.default_version";
inline constexpr char kSyncedDefaultPrivateSearchProviderGUID[] =
    "aiwize.default_private_search_provider_guid";
inline constexpr char kSyncedDefaultPrivateSearchProviderData[] =
    "aiwize.default_private_search_provider_data";

}  // namespace prefs

#endif  // BRAVE_CHROMIUM_SRC_COMPONENTS_SEARCH_ENGINES_SEARCH_ENGINES_PREF_NAMES_H_
