/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_CONSTANTS_PREF_NAMES_H_
#define BRAVE_COMPONENTS_CONSTANTS_PREF_NAMES_H_

#include "build/build_config.h"

inline constexpr char kBraveAutofillPrivateWindows[] =
    "aiwize.autofill_private_windows";
inline constexpr char kManagedBraveShieldsDisabledForUrls[] =
    "aiwize.managed_shields_disabled";
inline constexpr char kManagedBraveShieldsEnabledForUrls[] =
    "aiwize.managed_shields_enabled";
inline constexpr char kAdsBlocked[] = "aiwize.stats.ads_blocked";
// We no longer update this pref, but we keep it around for now because it's
// added to kAdsBlocked when being displayed.
inline constexpr char kTrackersBlocked[] = "aiwize.stats.trackers_blocked";
inline constexpr char kJavascriptBlocked[] = "aiwize.stats.javascript_blocked";
inline constexpr char kHttpsUpgrades[] = "aiwize.stats.https_upgrades";
inline constexpr char kFingerprintingBlocked[] =
    "aiwize.stats.fingerprinting_blocked";
inline constexpr char kLastCheckYMD[] = "aiwize.stats.last_check_ymd";
inline constexpr char kLastCheckWOY[] = "aiwize.stats.last_check_woy";
inline constexpr char kLastCheckMonth[] = "aiwize.stats.last_check_month";
inline constexpr char kFirstCheckMade[] = "aiwize.stats.first_check_made";
// Set to true if the user met the threshold requirements and successfully
// sent a ping to the stats-updater server.
inline constexpr char kThresholdCheckMade[] =
    "aiwize.stats.threshold_check_made";
// Anonymous usage pings enabled
inline constexpr char kStatsReportingEnabled[] =
    "aiwize.stats.reporting_enabled";
// Serialized query for to send to the stats-updater server. Needs to be saved
// in the case that the user sends the standard usage ping, stops the browser,
// meets the threshold requirements, and then starts the browser before the
// threshold ping was sent.
inline constexpr char kThresholdQuery[] = "aiwize.stats.threshold_query";
inline constexpr char kWeekOfInstallation[] =
    "aiwize.stats.week_of_installation";
inline constexpr char kWidevineEnabled[] = "aiwize.widevine_opted_in";
inline constexpr char kAskEnableWidvine[] = "aiwize.ask_widevine_install";
inline constexpr char kShowBookmarksButton[] = "aiwize.show_bookmarks_button";
inline constexpr char kShowSidePanelButton[] = "aiwize.show_side_panel_button";
inline constexpr char kLocationBarIsWide[] = "aiwize.location_bar_is_wide";
inline constexpr char kReferralDownloadID[] = "aiwize.referral.download_id";
inline constexpr char kReferralTimestamp[] = "aiwize.referral.timestamp";
inline constexpr char kReferralAttemptTimestamp[] =
    "aiwize.referral.referral_attempt_timestamp";
inline constexpr char kReferralAttemptCount[] =
    "aiwize.referral.referral_attempt_count";
inline constexpr char kReferralHeaders[] = "aiwize.referral.headers";
inline constexpr char kReferralAndroidFirstRunTimestamp[] =
    "aiwize.referral_android_first_run_timestamp";
inline constexpr char kNoScriptControlType[] = "aiwize.no_script_default";
inline constexpr char kShieldsAdvancedViewEnabled[] =
    "aiwize.shields.advanced_view_enabled";
inline constexpr char kShieldsStatsBadgeVisible[] =
    "aiwize.shields.stats_badge_visible";
inline constexpr char kAdControlType[] = "aiwize.ad_default";
inline constexpr char kGoogleLoginControlType[] = "aiwize.google_login_default";
inline constexpr char kWebTorrentEnabled[] = "aiwize.webtorrent_enabled";
inline constexpr char kHangoutsEnabled[] = "aiwize.hangouts_enabled";
inline constexpr char kIPFSCompanionEnabled[] = "aiwize.ipfs_companion_enabled";
inline constexpr char kNewTabPageShowClock[] = "aiwize.new_tab_page.show_clock";
inline constexpr char kNewTabPageClockFormat[] =
    "aiwize.new_tab_page.clock_format";
inline constexpr char kNewTabPageShowStats[] = "aiwize.new_tab_page.show_stats";
inline constexpr char kNewTabPageHideAllWidgets[] =
    "aiwize.new_tab_page.hide_all_widgets";
inline constexpr char kNewTabPageShowsOptions[] =
    "aiwize.new_tab_page.shows_options";
inline constexpr char kBraveNewsIntroDismissed[] =
    "aiwize.today.intro_dismissed";
inline constexpr char kAlwaysShowBookmarkBarOnNTP[] =
    "aiwize.always_show_bookmark_bar_on_ntp";
inline constexpr char kBraveDarkMode[] = "aiwize.dark_mode";
inline constexpr char kBraveShieldsSettingsVersion[] =
    "aiwize.shields_settings_version";
inline constexpr char kDefaultBrowserPromptEnabled[] =
    "aiwize.default_browser_prompt_enabled";

inline constexpr char kWebDiscoveryEnabled[] = "aiwize.web_discovery_enabled";
inline constexpr char kWebDiscoveryCTAState[] = "aiwize.web_discovery.cta_state";
inline constexpr char kDontAskEnableWebDiscovery[] =
    "aiwize.dont_ask_enable_web_discovery";
inline constexpr char kBraveSearchVisitCount[] =
    "aiwize.brave_search_visit_count";

inline constexpr char kBraveGCMChannelStatus[] = "aiwize.gcm.channel_status";
inline constexpr char kImportDialogExtensions[] = "import_dialog_extensions";
inline constexpr char kImportDialogPayments[] = "import_dialog_payments";
inline constexpr char kMRUCyclingEnabled[] = "aiwize.mru_cycling_enabled";
inline constexpr char kTabsSearchShow[] = "aiwize.tabs_search_show";
inline constexpr char kTabMuteIndicatorNotClickable[] =
    "aiwize.tabs.mute_indicator_not_clickable";
inline constexpr char kDontAskForCrashReporting[] =
    "aiwize.dont_ask_for_crash_reporting";

// Cast extension requires a browser restart once the setting is toggled.
// kEnableMediaRouterOnRestart is used as a proxy to identify the current
// state of the switch and prefs::kEnableMediaRouter is updated to
// kEnableMediaRouterOnRestart on restart.
inline constexpr char kEnableMediaRouterOnRestart[] =
    "aiwize.enable_media_router_on_restart";

#if BUILDFLAG(IS_ANDROID)
inline constexpr char kDesktopModeEnabled[] = "aiwize.desktop_mode_enabled";
inline constexpr char kPlayYTVideoInBrowserEnabled[] =
    "aiwize.play_yt_video_in_browser_enabled";
inline constexpr char kBackgroundVideoPlaybackEnabled[] =
    "aiwize.background_video_playback";
inline constexpr char kSafetynetCheckFailed[] = "safetynetcheck.failed";
inline constexpr char kSafetynetStatus[] = "safetynet.status";
#endif

#if !BUILDFLAG(IS_ANDROID)
inline constexpr char kEnableWindowClosingConfirm[] =
    "aiwize.enable_window_closing_confirm";
inline constexpr char kEnableClosingLastTab[] = "aiwize.enable_closing_last_tab";
#endif

inline constexpr char kDefaultBrowserLaunchingCount[] =
    "aiwize.default_browser.launching_count";

// deprecated
inline constexpr char kBraveThemeType[] = "aiwize.theme.type";
inline constexpr char kUseOverriddenBraveThemeType[] =
    "aiwize.theme.use_overridden_brave_theme_type";
inline constexpr char kNewTabPageShowTopSites[] =
    "aiwize.new_tab_page.show_top_sites";
inline constexpr char kOtherBookmarksMigrated[] =
    "aiwize.other_bookmarks_migrated";

// Obsolete widget removal prefs
#if !BUILDFLAG(IS_IOS) && !BUILDFLAG(IS_ANDROID)
inline constexpr char kFTXAccessToken[] = "aiwize.ftx.access_token";
inline constexpr char kFTXOauthHost[] = "aiwize.ftx.oauth_host";
inline constexpr char kFTXNewTabPageShowFTX[] = "ftx.new_tab_page.show_ftx";
inline constexpr char kCryptoDotComNewTabPageShowCryptoDotCom[] =
    "crypto_dot_com.new_tab_page.show_crypto_dot_com";
inline constexpr char kCryptoDotComHasBoughtCrypto[] =
    "crypto_dot_com.new_tab_page.has_bought_crypto";
inline constexpr char kCryptoDotComHasInteracted[] =
    "crypto_dot_com.new_tab_page.has_interacted";
inline constexpr char kGeminiAccessToken[] = "aiwize.gemini.access_token";
inline constexpr char kGeminiRefreshToken[] = "aiwize.gemini.refresh_token";
inline constexpr char kNewTabPageShowGemini[] =
    "aiwize.new_tab_page.show_gemini";
#endif

#if !BUILDFLAG(IS_IOS)
inline constexpr char kBinanceAccessToken[] = "aiwize.binance.access_token";
inline constexpr char kBinanceRefreshToken[] = "aiwize.binance.refresh_token";
inline constexpr char kNewTabPageShowBinance[] =
    "aiwize.new_tab_page.show_binance";
inline constexpr char kBraveSuggestedSiteSuggestionsEnabled[] =
    "aiwize.brave_suggested_site_suggestions_enabled";
#endif

#endif  // BRAVE_COMPONENTS_CONSTANTS_PREF_NAMES_H_
