// Copyright (c) 2021 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_COMPONENTS_BRAVE_NEWS_COMMON_PREF_NAMES_H_
#define BRAVE_COMPONENTS_BRAVE_NEWS_COMMON_PREF_NAMES_H_

namespace brave_news {
namespace prefs {

inline constexpr char kNewTabPageShowToday[] =
    "aiwize.new_tab_page.show_brave_news";
inline constexpr char kBraveNewsSources[] = "aiwize.today.sources";
inline constexpr char kBraveNewsChannels[] = "aiwize.news.channels";
inline constexpr char kBraveNewsDirectFeeds[] = "aiwize.today.userfeeds";
inline constexpr char kBraveNewsIntroDismissed[] =
    "aiwize.today.intro_dismissed";
inline constexpr char kBraveNewsOptedIn[] = "aiwize.today.opted_in";
inline constexpr char kBraveNewsDaysInMonthUsedCount[] =
    "aiwize.today.p3a_days_in_month_count";
inline constexpr char kShouldShowToolbarButton[] =
    "aiwize.today.should_show_toolbar_button";
inline constexpr char kBraveNewsWeeklySessionCount[] =
    "aiwize.today.p3a_weekly_session_count";
inline constexpr char kBraveNewsWeeklyCardViewsCount[] =
    "aiwize.today.p3a_weekly_card_views_count";
inline constexpr char kBraveNewsWeeklyCardVisitsCount[] =
    "aiwize.today.p3a_weekly_card_visits_count";
inline constexpr char kBraveNewsWeeklyDisplayAdViewedCount[] =
    "aiwize.today.p3a_weekly_display_ad_viewed_count";
inline constexpr char kBraveNewsWeeklyAddedDirectFeedsCount[] =
    "aiwize.today.p3a_weekly_added_direct_feeds_count";
inline constexpr char kBraveNewsTotalCardViews[] =
    "aiwize.today.p3a_total_card_views";
inline constexpr char kBraveNewsCurrSessionCardViews[] =
    "aiwize.today.p3a_curr_session_card_views";
inline constexpr char kBraveNewsFirstSessionTime[] =
    "aiwize.today.p3a_first_session_time";
inline constexpr char kBraveNewsUsedSecondDay[] =
    "aiwize.today.p3a_used_second_day";
inline constexpr char kBraveNewsLastSessionTime[] =
    "aiwize.today.p3a_last_session_time";
inline constexpr char kBraveNewsWasEverEnabled[] =
    "aiwize.today.p3a_was_ever_enabled";
inline constexpr char kBraveNewsOpenArticlesInNewTab[] =
    "aiwize.news.open-articles-in-new-tab";

// Dictionary value keys
inline constexpr char kBraveNewsDirectFeedsKeyTitle[] = "title";
inline constexpr char kBraveNewsDirectFeedsKeySource[] = "source";

}  // namespace prefs

}  // namespace brave_news

#endif  // BRAVE_COMPONENTS_BRAVE_NEWS_COMMON_PREF_NAMES_H_
