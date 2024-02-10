/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/decentralized_dns/core/utils.h"

#include <string_view>

#include "base/strings/string_util.h"
#include "brave/components/decentralized_dns/core/constants.h"
#include "brave/components/decentralized_dns/core/pref_names.h"
#include "brave/net/decentralized_dns/constants.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace decentralized_dns {

void RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  registry->RegisterIntegerPref(kUnstoppableDomainsResolveMethod,
                                static_cast<int>(ResolveMethodTypes::ASK));
}

void MigrateObsoleteLocalStatePrefs(PrefService* local_state) {
  // Added 05/2022
  if (static_cast<int>(ResolveMethodTypes::DEPRECATED_DNS_OVER_HTTPS) ==
      local_state->GetInteger(kUnstoppableDomainsResolveMethod)) {
    local_state->ClearPref(kUnstoppableDomainsResolveMethod);
  }
}

bool IsUnstoppableDomainsTLD(const std::string_view host) {
  for (auto* domain : kUnstoppableDomains) {
    if (base::EndsWith(host, domain)) {
      return true;
    }
  }
  return false;
}

void SetUnstoppableDomainsResolveMethod(PrefService* local_state,
                                        ResolveMethodTypes method) {
  local_state->SetInteger(kUnstoppableDomainsResolveMethod,
                          static_cast<int>(method));
}

ResolveMethodTypes GetUnstoppableDomainsResolveMethod(
    PrefService* local_state) {
  return static_cast<ResolveMethodTypes>(
      local_state->GetInteger(kUnstoppableDomainsResolveMethod));
}

bool IsUnstoppableDomainsResolveMethodAsk(PrefService* local_state) {
  if (!local_state) {
    return false;  // Treat it as disabled.
  }

  return GetUnstoppableDomainsResolveMethod(local_state) ==
         ResolveMethodTypes::ASK;
}

bool IsUnstoppableDomainsResolveMethodEnabled(PrefService* local_state) {
  if (!local_state) {
    return false;  // Treat it as disabled.
  }

  return GetUnstoppableDomainsResolveMethod(local_state) ==
         ResolveMethodTypes::ENABLED;
}


}  // namespace decentralized_dns
