/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_MISC_METRICS_PREF_NAMES_H_
#define BRAVE_COMPONENTS_MISC_METRICS_PREF_NAMES_H_

namespace misc_metrics {
inline constexpr char kMiscMetricsBrowserUsageList[] =
    "aiwize.misc_metrics.browser_usage";
inline constexpr char kMiscMetricsMenuDismissStorage[] =
    "aiwize.misc_metrics.menu_dismiss_storage";
inline constexpr char kMiscMetricsMenuGroupActionCounts[] =
    "aiwize.misc_metrics.menu_group_actions";
inline constexpr char kMiscMetricsMenuShownStorage[] =
    "aiwize.misc_metrics.menu_shown_storage";
inline constexpr char kMiscMetricsPagesLoadedCount[] =
    "aiwize.core_metrics.pages_loaded";
inline constexpr char kMiscMetricsPrivacyHubViews[] =
    "aiwize.misc_metrics.privacy_hub_views";
inline constexpr char kMiscMetricsOpenTabsStorage[] =
    "aiwize.misc_metrics.open_tabs_storage";
inline constexpr char kMiscMetricsGroupTabsStorage[] =
    "aiwize.misc_metrics.group_tabs_storage";
inline constexpr char kMiscMetricsPinnedTabsStorage[] =
    "aiwize.misc_metrics.pinned_tabs_storage";

inline constexpr char kMiscMetricsSearchSwitchedAwayFromBrave[] =
    "aiwize.misc_metrics.search_switched_from_brave";
inline constexpr char kMiscMetricsSearchBraveQueryCount[] =
    "aiwize.misc_metrics.search_brave_query_count";

inline constexpr char kMiscMetricsTotalDnsRequestStorage[] =
    "aiwize.misc_metrics.total_dns_requests";
inline constexpr char kMiscMetricsUpgradedDnsRequestStorage[] =
    "aiwize.misc_metrics.upgraded_dns_requests";

inline constexpr char kDailyUptimesListPrefName[] =
    "daily_uptimes";  // DEPRECATED
inline constexpr char kDailyUptimeSumPrefName[] =
    "aiwize.misc_metrics.uptime_sum";
inline constexpr char kDailyUptimeFrameStartTimePrefName[] =
    "aiwize.misc_metrics.uptime_frame_start_time";

inline constexpr char kMiscMetricsTabSwitcherNewTabsStorage[] =
    "aiwize.misc_metrics.tab_switcher_new_tabs_storage";
inline constexpr char kMiscMetricsTotalNewTabsStorage[] =
    "aiwize.misc_metrics.total_new_tabs_storage";
inline constexpr char kMiscMetricsNewTabLocationBarEntriesStorage[] =
    "aiwize.misc_metrics.new_tab_location_bar_entries_storage";
inline constexpr char kMiscMetricsTotalLocationBarEntriesStorage[] =
    "aiwize.misc_metrics.total_location_bar_entries_storage";
}  // namespace misc_metrics

#endif  // BRAVE_COMPONENTS_MISC_METRICS_PREF_NAMES_H_
