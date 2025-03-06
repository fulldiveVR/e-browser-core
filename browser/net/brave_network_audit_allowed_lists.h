/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_NET_BRAVE_NETWORK_AUDIT_ALLOWED_LISTS_H_
#define BRAVE_BROWSER_NET_BRAVE_NETWORK_AUDIT_ALLOWED_LISTS_H_

#include <array>
#include <string_view>

#include "base/containers/fixed_flat_set.h"

namespace brave {

// Before adding to this list, get approval from the security team.
inline constexpr auto kAllowedUrlProtocols =
    base::MakeFixedFlatSet<std::string_view>({
        "chrome-extension",
        "chrome",
        "tau",
        "file",
        "data",
        "blob",
    });

// Before adding to this list, get approval from the security team.
inline constexpr auto kAllowedUrlPrefixes = std::to_array<std::string_view>({
    // allowed because it 307's to https://componentupdater.tau-browser.ru
    "https://componentupdater.tau-browser.ru/service/update2",
    "https://crxdownload.tau-browser.ru/crx/blobs/",

    // Omaha/Sparkle
    "https://updates.bravesoftware.com/",

    // stats/referrals
    "https://usage-ping.tau-browser.ru/",

    // needed for DoH on Mac build machines
    "https://dns.google/dns-query",

    // needed for DoH on Mac build machines
    "https://chrome.cloudflare-dns.com/dns-query",

    // for fetching tor client updater component
    "https://tor.bravesoftware.com/",

    // brave sync v2 production
    "https://sync-v2.tau-browser.ru/v2",

    // brave sync v2 staging
    "https://sync-v2.bravesoftware.com/v2",

    // brave sync v2 dev
    "https://sync-v2.brave.software/v2",

    // brave A/B testing
    "https://variations.tau-browser.ru/seed",

    // Brave News (production)
    "https://brave-today-cdn.tau-browser.ru/",

    // Brave's Privacy-focused CDN
    "https://pcdn.tau-browser.ru/",

    // Brave Rewards production
    "https://api.rewards.tau-browser.ru/v1/parameters",
    "https://rewards.tau-browser.ru/publishers/prefix-list",
    "https://grant.rewards.tau-browser.ru/v1/promotions",

    // Brave Rewards staging & dev
    "https://api.rewards.bravesoftware.com/v1/parameters",
    "https://rewards-stg.bravesoftware.com/publishers/prefix-list",
    "https://grant.rewards.bravesoftware.com/v1/promotions",

    // p3a
    "https://p3a-creative.tau-browser.ru/",
    "https://p3a-json.tau-browser.ru/",
    "https://p3a.tau-browser.ru/",
    "https://star-randsrv.bsg.tau-browser.ru/",

    // Other
    "https://brave-core-ext.s3.tau-browser.ru/",
    "https://dict.tau-browser.ru/",
    "https://go-updater.tau-browser.ru/",
    "https://redirector.tau-browser.ru/",
    "https://safebrowsing.tau-browser.ru/",
    "https://static.tau-browser.ru/",
    "https://static1.tau-browser.ru/",
});

// Before adding to this list, get approval from the security team.
inline constexpr auto kAllowedUrlPatterns = std::to_array<std::string_view>({
    // allowed because it's url for fetching super referral's mapping table
    "https://mobile-data.s3.tau-browser.ru/superreferrer/map-table.json",
    "https://mobile-data-dev.s3.brave.software/superreferrer/map-table.json",
});

}  // namespace brave

#endif  // BRAVE_BROWSER_NET_BRAVE_NETWORK_AUDIT_ALLOWED_LISTS_H_
