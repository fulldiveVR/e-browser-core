// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/webui/webui_resources.h"

#include <vector>

#include "base/containers/flat_map.h"
#include "base/no_destructor.h"
#include "base/strings/utf_string_conversions.h"
#include "brave/components/brave_vpn/common/buildflags/buildflags.h"
#include "brave/components/constants/url_constants.h"
#include "build/build_config.h"
#include "components/grit/brave_components_resources.h"
#include "components/grit/brave_components_strings.h"
#include "components/grit/components_resources.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/webui/resource_path.h"
#include "ui/base/webui/web_ui_util.h"

#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)
#endif

namespace brave {

base::span<const webui::ResourcePath> GetWebUIResources(
    std::string_view webui_name) {
  static const base::NoDestructor<
      base::flat_map<std::string_view, std::vector<webui::ResourcePath>>>
      kResources{{
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)
          {"newtab",
           {{"img/toolbar/menu_btn.svg", IDR_BRAVE_COMMON_TOOLBAR_IMG},
            // Hash path is the MD5 of the file contents,
            // webpack image loader does this
            {"fd85070af5114d6ac462c466e78448e4.svg", IDR_BRAVE_NEW_TAB_IMG1},
            {"314e7529efec41c8867019815f4d8dad.svg", IDR_BRAVE_NEW_TAB_IMG4},
            {"6c337c63662ee0ba4e57f6f8156d69ce.svg", IDR_BRAVE_NEW_TAB_IMG2},
            // New tab Backgrounds
            {"wallpaper.webp", IDR_BRAVE_NEW_TAB_BACKGROUND1},
            // private tab
            {"dbdc336ccc651b8a7c925b3482d6e65a.svg",
             IDR_BRAVE_PRIVATE_TAB_IMG}}},
          {"welcome", {{"favicon.ico", IDR_BRAVE_WELCOME_PAGE_FAVICON}}},
#endif
          {"adblock", {}},
      }};

  if (auto it = kResources->find(webui_name); it != kResources->end()) {
    return it->second;
  }
  return {};
}  // NO-LINT (readability/fn_size)

base::span<const webui::LocalizedString> GetWebUILocalizedStrings(
    std::string_view webui_name) {
  static const base::NoDestructor<
      base::flat_map<std::string_view, std::vector<webui::LocalizedString>>>
      kLocalizedStrings{{
          {"newtab",
           {
               {"adsTrackersBlocked",
                IDS_BRAVE_NEW_TAB_TOTAL_ADS_TRACKERS_BLOCKED},
               {"httpsUpgraded", IDS_BRAVE_NEW_TAB_TOTAL_HTTPS_UPGRADES},
               {"estimatedTimeSaved", IDS_BRAVE_NEW_TAB_TOTAL_TIME_SAVED},
               {"estimatedBandwidthSaved",
                IDS_BRAVE_NEW_TAB_ESTIMATED_BANDWIDTH_SAVED},
               {"thumbRemoved", IDS_BRAVE_NEW_TAB_THUMB_REMOVED},
               {"undoRemoved", IDS_BRAVE_NEW_TAB_UNDO_REMOVED},
               {"close", IDS_BRAVE_NEW_TAB_CLOSE},
               {"restoreAll", IDS_BRAVE_NEW_TAB_RESTORE_ALL},
               {"second", IDS_BRAVE_NEW_TAB_SECOND},
               {"seconds", IDS_BRAVE_NEW_TAB_SECONDS},
               {"minute", IDS_BRAVE_NEW_TAB_MINUTE},
               {"minutes", IDS_BRAVE_NEW_TAB_MINUTES},
               {"hour", IDS_BRAVE_NEW_TAB_HOUR},
               {"hours", IDS_BRAVE_NEW_TAB_HOURS},
               {"day", IDS_BRAVE_NEW_TAB_DAY},
               {"days", IDS_BRAVE_NEW_TAB_DAYS},
               {"B", IDS_BRAVE_NEW_TAB_BYTES},
               {"KB", IDS_BRAVE_NEW_TAB_KILOBYTES},
               {"MB", IDS_BRAVE_NEW_TAB_MEGABYTES},
               {"GB", IDS_BRAVE_NEW_TAB_GIGABYTES},
               {"photoBy", IDS_BRAVE_NEW_TAB_PHOTO_BY},
               {"hide", IDS_BRAVE_NEW_TAB_HIDE},
               {"dashboardSettingsTitle",
                IDS_BRAVE_NEW_TAB_DASHBOARD_SETTINGS_TITLE},
               {"customize", IDS_BRAVE_NEW_TAB_CUSTOMIZE},
               {"showBackgroundImage", IDS_BRAVE_NEW_TAB_SHOW_BACKGROUND_IMAGE},
               {"braveBackgroundImageOptionTitle",
                IDS_BRAVE_NEW_TAB_BRAVE_BACKGROUND_IMAGE_OPTION_TITLE},
               {"customBackgroundImageOptionTitle",
                IDS_BRAVE_NEW_TAB_CUSTOM_BACKGROUND_IMAGE_OPTION_TITLE},
               {"customBackgroundImageOptionUploadLabel",
                IDS_BRAVE_NEW_TAB_CUSTOM_BACKGROUND_IMAGE_OPTION_UPLOAD_LABEL},
               {"showBraveStats", IDS_BRAVE_NEW_TAB_SHOW_BRAVE_STATS},
               {"showClock", IDS_BRAVE_NEW_TAB_SHOW_CLOCK},
               {"clockFormat", IDS_BRAVE_NEW_TAB_CLOCK_FORMAT},
               {"clockFormatDefault", IDS_BRAVE_NEW_TAB_CLOCK_FORMAT_DEFAULT},
               {"clockFormat12", IDS_BRAVE_NEW_TAB_CLOCK_FORMAT_12},
               {"clockFormat24", IDS_BRAVE_NEW_TAB_CLOCK_FORMAT_24},
               {"addTopSiteDialogTitle",
                IDS_BRAVE_NEW_TAB_ADD_TOP_SITE_DIALOG_TITLE},
               {"editTopSiteDialogTitle",
                IDS_BRAVE_NEW_TAB_EDIT_TOP_SITE_DIALOG_TITLE},
               {"editSiteTileMenuItem",
                IDS_BRAVE_NEW_TAB_EDIT_SITE_TILE_MENU_ITEM},
               {"removeTileMenuItem", IDS_BRAVE_NEW_TAB_REMOVE_TILE_MENU_ITEM},
               {"addTopSiteDialogURLLabel",
                IDS_BRAVE_NEW_TAB_ADD_TOP_SITE_DIALOG_URL_LABEL},
               {"addTopSiteDialogURLInputPlaceHolder",
                IDS_BRAVE_NEW_TAB_ADD_TOP_SITE_DIALOG_URL_INPUT_PLACEHOLDER},
               {"addTopSiteDialogNameLabel",
                IDS_BRAVE_NEW_TAB_ADD_TOP_SITE_DIALOG_NAME_LABEL},
               {"addTopSiteDialogNameInputPlaceHolder",
                IDS_BRAVE_NEW_TAB_ADD_TOP_SITE_DIALOG_NAME_INPUT_PLACEHOLDER},
               {"addTopSiteDialogSaveButtonLabel",
                IDS_BRAVE_NEW_TAB_ADD_TOP_SITE_DIALOG_SAVE_BUTTON_LABEL},
               {"addTopSiteDialogCancelButtonLabel",
                IDS_BRAVE_NEW_TAB_ADD_TOP_SITE_DIALOG_CANCEL_BUTTON_LABEL},
               {"showTopSites", IDS_BRAVE_NEW_TAB_SHOW_TOP_SITES},
               {"showFavoritesLabel", IDS_BRAVE_NEW_TAB_SHOW_FAVORITES_LABEL},
               {"showFavoritesDesc", IDS_BRAVE_NEW_TAB_SHOW_FAVORITES_DESC},
               {"showFrecencyLabel", IDS_BRAVE_NEW_TAB_SHOW_FRECENCY_LABEL},
               {"showFrecencyDesc", IDS_BRAVE_NEW_TAB_SHOW_FRECENCY_DESC},
               {"addSiteMenuLabel", IDS_BRAVE_NEW_TAB_ADD_SITE_MENU_LABEL},
               {"showFrecencyMenuLabel",
                IDS_BRAVE_NEW_TAB_SHOW_FRECENCY_MENU_LABEL},
               {"showFavoritesMenuLabel",
                IDS_BRAVE_NEW_TAB_SHOW_FAVORITES_MENU_LABEL},
               {"searchCustomizeList", IDS_BRAVE_NEW_TAB_SEARCH_CUSTOMIZE_LIST},
               {"searchBravePlaceholder",
                IDS_BRAVE_NEW_TAB_SEARCH_BRAVE_PLACEHOLDER},
               {"searchHide", IDS_BRAVE_NEW_TAB_SEARCH_HIDE_SEARCH},
               {"searchAskLeo", IDS_OMNIBOX_ASK_LEO_DESCRIPTION},
               {"searchNonBravePlaceholder",
                IDS_BRAVE_NEW_TAB_SEARCH_NON_BRAVE_PLACEHOLDER},
               {"searchShowSetting", IDS_BRAVE_NEW_TAB_SEARCH_SHOW_SETTING},
               {"searchEnableSearchEnginesTitle",
                IDS_BRAVE_NEW_TAB_SEARCH_ENABLE_SEARCH_ENGINES_TITLE},
               {"searchCustomizeSearchEngines",
                IDS_BRAVE_NEW_TAB_SEARCH_CUSTOMIZE_SEARCH_ENGINES},
               {"searchEnableSuggestionsPromptTitle",
                IDS_BRAVE_NEW_TAB_SEARCH_ENABLE_SEARCH_SUGGESTIONS_TITLE},
               {"searchEnableSuggestionsPromptExplanation",
                IDS_BRAVE_NEW_TAB_SEARCH_ENABLE_SEARCH_SUGGESTIONS_EXPLANATION},
               {"searchEnableSuggestionsPromptEnable",
                IDS_BRAVE_NEW_TAB_SEARCH_ENABLE_SEARCH_SUGGESTIONS_ENABLE},
               {"searchEnableSuggestionsPromptDismiss",
                IDS_BRAVE_NEW_TAB_SEARCH_ENABLE_SEARCH_SUGGESTIONS_DISMISS},
               {"cards", IDS_BRAVE_NEW_TAB_SHOW_CARDS},
               {"brandedWallpaperOptIn",
                IDS_BRAVE_NEW_TAB_BRANDED_WALLPAPER_OPT_IN},
               {"sponsoredImageEarningTitle",
                IDS_BRAVE_NEW_TAB_SPONSORED_IMAGE_EARNING_TITLE},
               {"sponsoredImageNotEarningTitle",
                IDS_BRAVE_NEW_TAB_SPONSORED_IMAGE_NOT_EARNING_TITLE},
               {"sponsoredImageOnDescription",
                IDS_BRAVE_NEW_TAB_SPONSORED_IMAGE_ON_DESCRIPTION},
               {"topSitesTitle", IDS_BRAVE_NEW_TAB_TOP_SITES},
               {"statsTitle", IDS_BRAVE_NEW_TAB_STATS},
               {"clockTitle", IDS_BRAVE_NEW_TAB_CLOCK},
               {"searchTitle", IDS_BRAVE_NEW_TAB_SEARCH},
               {"backgroundImageTitle", IDS_BRAVE_NEW_TAB_BACKGROUND_IMAGE},
               {"settingsNavigateBack", IDS_BRAVE_NEW_TAB_SETTINGS_BACK},
               {"braveBackgroundsTitle", IDS_BRAVE_NEW_TAB_BRAVE_BACKGROUND},
               {"solidColorTitle", IDS_BRAVE_NEW_TAB_SOLID_COLOR},
               {"gradientColorTitle", IDS_BRAVE_NEW_TAB_GRADIENT_COLOR},
               {"refreshBackgroundOnNewTab",
                IDS_BRAVE_NEW_TAB_REFRESH_BACKGROUND_ON_NEW_TAB},

               // search promotion
               {"searchPromotionNTPPopupTitle1",
                IDS_BRAVE_NEW_TAB_SEARCH_PROMOTION_POPUP_TITLE_1},
               {"searchPromotionNTPPopupTitle2",
                IDS_BRAVE_NEW_TAB_SEARCH_PROMOTION_POPUP_TITLE_2},
               {"searchPromotionNTPPopupDesc",
                IDS_BRAVE_NEW_TAB_SEARCH_PROMOTION_POPUP_DESC},
               {"searchPromotionNTPPopupBottom",
                IDS_BRAVE_NEW_TAB_SEARCH_PROMOTION_POPUP_BOTTOM},
               {"searchPromotionSearchBoxPlaceholderLabel",
                IDS_BRAVE_NEW_TAB_SEARCH_PROMOTION_SEARCH_BOX_PLACEHOLDER},

               {"braveNewsTitle", IDS_BRAVE_NEWS_TITLE},
               {"braveNewsStatusFetching", IDS_BRAVE_NEWS_STATUS_FETCHING},
               {"braveNewsActionRefresh", IDS_BRAVE_NEWS_ACTION_REFRESH},
               {"braveNewsScrollHint", IDS_BRAVE_NEWS_SCROLL_HINT},
               {"braveNewsResetAction", IDS_BRAVE_NEWS_RESET_ACTION},
               {"braveNewsResetConfirm", IDS_BRAVE_NEWS_RESET_CONFIRM},
               {"braveNewsCategoryNameAll", IDS_BRAVE_NEWS_CATEGORY_NAME_ALL},
               {"braveNewsSourcesTitle", IDS_BRAVE_NEWS_SOURCES_TITLE},
               {"braveNewsDisableSourceCommand",
                IDS_BRAVE_NEWS_DISABLE_SOURCE_COMMAND},
               {"promoted", IDS_BRAVE_NEWS_PROMOTED},
               {"ad", IDS_BRAVE_NEWS_DISPLAY_AD_LABEL},

               {"braveNewsIntroTitle", IDS_BRAVE_NEWS_INTRO_TITLE},
               {"braveNewsIntroDescription", IDS_BRAVE_NEWS_INTRO_DESCRIPTION},
               {"braveNewsIntroDescriptionTwo",
                IDS_BRAVE_NEWS_INTRO_DESCRIPTION_TWO},
               {"braveNewsOptInActionLabel",
                IDS_BRAVE_NEWS_OPT_IN_ACTION_LABEL},
               {"braveNewsOptOutActionLabel",
                IDS_BRAVE_NEWS_OPT_OUT_ACTION_LABEL},
               {"braveNewsBackToDashboard", IDS_BRAVE_NEWS_BACK_TO_DASHBOARD},
               {"braveNewsBackButton", IDS_BRAVE_NEWS_BACK_BUTTON},
               {"braveNewsSearchPlaceholderLabel",
                IDS_BRAVE_NEWS_SEARCH_PLACEHOLDER_LABEL},
               {"braveNewsChannelsHeader",
                IDS_BRAVE_NEWS_BROWSE_CHANNELS_HEADER},
               {"braveNewsViewAllButton", IDS_BRAVE_NEWS_VIEW_ALL_BUTTON},
               {"braveNewsAllSourcesHeader", IDS_BRAVE_NEWS_ALL_SOURCES_HEADER},
               {"braveNewsFeedsHeading", IDS_BRAVE_NEWS_FEEDS_HEADING},
               {"braveNewsFollowButtonFollowing",
                IDS_BRAVE_NEWS_FOLLOW_BUTTON_FOLLOWING},
               {"braveNewsFollowButtonNotFollowing",
                IDS_BRAVE_NEWS_FOLLOW_BUTTON_NOT_FOLLOWING},
               {"braveNewsDirectSearchButton",
                IDS_BRAVE_NEWS_DIRECT_SEARCH_BUTTON},
               {"braveNewsDirectSearchNoResults",
                IDS_BRAVE_NEWS_DIRECT_SEARCH_NO_RESULTS},
               {"braveNewsSearchResultsNoResults",
                IDS_BRAVE_NEWS_SEARCH_RESULTS_NO_RESULTS},
               {"braveNewsSearchResultsLocalResults",
                IDS_BRAVE_NEWS_SEARCH_RESULTS_LOCAL_RESULTS},
               {"braveNewsSearchResultsDirectResults",
                IDS_BRAVE_NEWS_SEARCH_RESULTS_DIRECT_RESULTS},
               {"braveNewsSearchQueryTooShort",
                IDS_BRAVE_NEWS_SEARCH_QUERY_TOO_SHORT},
               {"braveNewsSuggestionsTitle", IDS_BRAVE_NEWS_SUGGESTIONS_TITLE},
               {"braveNewsSuggestionsSubtitle",
                IDS_BRAVE_NEWS_SUGGESTIONS_SUBTITLE},
               {"braveNewsErrorHeading", IDS_BRAVE_NEWS_ERROR_HEADING},
               {"braveNewsErrorMessage", IDS_BRAVE_NEWS_ERROR_MESSAGE},
               {"braveNewsErrorActionLabel", IDS_BRAVE_NEWS_ERROR_ACTION_LABEL},
               {"braveNewsNoContentHeading", IDS_BRAVE_NEWS_NO_CONTENT_HEADING},
               {"braveNewsNoContentMessage", IDS_BRAVE_NEWS_NO_CONTENT_MESSAGE},
               {"braveNewsNoContentActionLabel",
                IDS_BRAVE_NEWS_NO_CONTENT_ACTION_LABEL},
               {"braveNewsPopularTitle", IDS_BRAVE_NEWS_POPULAR_TITLE},
               {"braveNewsNewsPeek", IDS_BRAVE_NEWS_NEWS_PEEK},
               {"braveNewsForYouFeed", IDS_BRAVE_NEWS_FOR_YOU_FEED},
               {"braveNewsFollowingFeed", IDS_BRAVE_NEWS_FOLLOWING_FEED},
               {"braveNewsPublishersHeading",
                IDS_BRAVE_NEWS_PUBLISHERS_HEADING},
               {"braveNewsShowAll", IDS_BRAVE_NEWS_SHOW_ALL},
               {"braveNewsShowLess", IDS_BRAVE_NEWS_SHOW_LESS},
               {"braveNewsAdvertBadge", IDS_BRAVE_NEWS_ADVERT_BADGE},
               {"braveNewsHideContentFrom", IDS_BRAVE_NEWS_HIDE_CONTENT_FROM},
               {"braveNewsSourcesRecommendation",
                IDS_BRAVE_NEWS_SOURCES_RECOMMENDATION},
               {"braveNewsNoArticlesTitle", IDS_BRAVE_NEWS_NO_ARTICLES_TITLE},
               {"braveNewsNoArticlesMessage",
                IDS_BRAVE_NEWS_NO_ARTICLES_MESSAGE},
               {"braveNewsOfflineTitle", IDS_BRAVE_NEWS_OFFLINE_TITLE},
               {"braveNewsOfflineMessage", IDS_BRAVE_NEWS_OFFLINE_MESSAGE},
               {"braveNewsCustomizeFeed", IDS_BRAVE_NEWS_CUSTOMIZE_FEED},
               {"braveNewsRefreshFeed", IDS_BRAVE_NEWS_REFRESH_FEED},
               {"braveNewsOpenArticlesIn", IDS_BRAVE_NEWS_OPEN_ARTICLES_IN},
               {"braveNewsOpenArticlesInNewTab",
                IDS_BRAVE_NEWS_OPEN_ARTICLES_IN_NEW_TAB},
               {"braveNewsOpenArticlesInCurrentTab",
                IDS_BRAVE_NEWS_OPEN_ARTICLES_IN_CURRENT_TAB},
               {"braveNewsCaughtUp", IDS_BRAVE_NEWS_CAUGHT_UP},
               {"braveNewsNewContentAvailable",
                IDS_BRAVE_NEWS_NEW_CONTENT_AVAILABLE},

               // Brave News Channels
               {"braveNewsChannel-Brave", IDS_BRAVE_NEWS_CHANNEL_BRAVE},
               {"braveNewsChannel-Business", IDS_BRAVE_NEWS_CHANNEL_BUSINESS},
               {"braveNewsChannel-Cars", IDS_BRAVE_NEWS_CHANNEL_CARS},
               {"braveNewsChannel-Celebrities",
                IDS_BRAVE_NEWS_CHANNEL_CELEBRITIES},
               {"braveNewsChannel-Crypto", IDS_BRAVE_NEWS_CHANNEL_CRYPTO},
               {"braveNewsChannel-Culture", IDS_BRAVE_NEWS_CHANNEL_CULTURE},
               {"braveNewsChannel-Education", IDS_BRAVE_NEWS_CHANNEL_EDUCATION},
               {"braveNewsChannel-Entertainment",
                IDS_BRAVE_NEWS_CHANNEL_ENTERTAINMENT},
               {"braveNewsChannel-Fashion", IDS_BRAVE_NEWS_CHANNEL_FASHION},
               {"braveNewsChannel-Film and TV",
                IDS_BRAVE_NEWS_CHANNEL_FILM_AND_TV},
               {"braveNewsChannel-Food", IDS_BRAVE_NEWS_CHANNEL_FOOD},
               {"braveNewsChannel-Fun", IDS_BRAVE_NEWS_CHANNEL_FUN},
               {"braveNewsChannel-Gaming", IDS_BRAVE_NEWS_CHANNEL_GAMING},
               {"braveNewsChannel-Health", IDS_BRAVE_NEWS_CHANNEL_HEALTH},
               {"braveNewsChannel-Home", IDS_BRAVE_NEWS_CHANNEL_HOME},
               {"braveNewsChannel-Lifestyle", IDS_BRAVE_NEWS_CHANNEL_LIFESTYLE},
               {"braveNewsChannel-Music", IDS_BRAVE_NEWS_CHANNEL_MUSIC},
               {"braveNewsChannel-Politics", IDS_BRAVE_NEWS_CHANNEL_POLITICS},
               {"braveNewsChannel-Regional News",
                IDS_BRAVE_NEWS_CHANNEL_REGIONAL_NEWS},
               {"braveNewsChannel-Science", IDS_BRAVE_NEWS_CHANNEL_SCIENCE},
               {"braveNewsChannel-Sports", IDS_BRAVE_NEWS_CHANNEL_SPORTS},
               {"braveNewsChannel-Travel", IDS_BRAVE_NEWS_CHANNEL_TRAVEL},
               {"braveNewsChannel-Technology",
                IDS_BRAVE_NEWS_CHANNEL_TECHNOLOGY},
               {"braveNewsChannel-Top News", IDS_BRAVE_NEWS_CHANNEL_TOP_NEWS},
               {"braveNewsChannel-Top Sources",
                IDS_BRAVE_NEWS_CHANNEL_TOP_SOURCES},
               {"braveNewsChannel-UK News", IDS_BRAVE_NEWS_CHANNEL_UK_NEWS},
               {"braveNewsChannel-US News", IDS_BRAVE_NEWS_CHANNEL_US_NEWS},
               {"braveNewsChannel-Weather", IDS_BRAVE_NEWS_CHANNEL_WEATHER},
               {"braveNewsChannel-World News",
                IDS_BRAVE_NEWS_CHANNEL_WORLD_NEWS},

               {"addWidget", IDS_BRAVE_NEW_TAB_WIDGET_ADD},
               {"hideWidget", IDS_BRAVE_NEW_TAB_WIDGET_HIDE},
               {"cardsToggleTitle", IDS_BRAVE_NEW_TAB_CARDS_TITLE},
               {"cardsToggleDesc", IDS_BRAVE_NEW_TAB_CARDS_DESC},
               {"editCardsTitle", IDS_EDIT_CARDS_TITLE},
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)
               // Private Tab - General
               {"learnMore", IDS_BRAVE_PRIVATE_NEW_TAB_LEARN_MORE},
               {"done", IDS_BRAVE_PRIVATE_NEW_TAB_DONE},
               {"headerLabel", IDS_BRAVE_PRIVATE_NEW_TAB_THIS_IS_A},

               // Private Tab - Header Private Window
               {"headerTitle", IDS_BRAVE_PRIVATE_NEW_TAB_PRIVATE_WINDOW},
               {"headerText", IDS_BRAVE_PRIVATE_NEW_TAB_PRIVATE_WINDOW_DESC},
               {"headerText1", IDS_BRAVE_PRIVATE_NEW_TAB_PRIVATE_WINDOW_DESC1},
               {"headerText2", IDS_BRAVE_PRIVATE_NEW_TAB_PRIVATE_WINDOW_DESC2},
               {"headerButton",
                IDS_BRAVE_PRIVATE_NEW_TAB_PRIVATE_WINDOW_BUTTON},

               // Private Tab - Header Private Window with Tor

               // Private Tab - Box for DDG
               {"boxDdgButton", IDS_BRAVE_PRIVATE_NEW_TAB_BOX_DDG_BUTTON},

               // Private Tab - Box for Tor

               // Private Tab - Private Window with Tor - Tor Box

               // Private Tab - Private Window - Tor Box
#endif  // !BUILDFLAG(IS_ANDROID)

               // Rewards widget


#if BUILDFLAG(ENABLE_BRAVE_VPN) & !BUILDFLAG(IS_ANDROID)
               // Brave VPN Widget
               {"braveVpnWidgetTitle", IDS_BRAVE_VPN_WIDGET_TITLE},
               {"braveVpnWidgetSettingTitle", IDS_BRAVE_VPN_WIDGET_TITLE},
               {"braveVpnWidgetSettingDesc", IDS_BRAVE_VPN_WIDGET_SETTING_DESC},
               {"braveVpnFeature1", IDS_BRAVE_VPN_FEATURE_1},
               {"braveVpnFeature2", IDS_BRAVE_VPN_FEATURE_2},
               {"braveVpnWidgetFeature3", IDS_BRAVE_VPN_WIDGET_FEATURE_3},
               {"braveVpnConnected", IDS_BRAVE_VPN_CONNECTED},
               {"braveVpnConnecting", IDS_BRAVE_VPN_CONNECTING},
               {"braveVpnDisconnected", IDS_BRAVE_VPN_DISCONNECTED},
               {"braveVpnDisconnecting", IDS_BRAVE_VPN_DISCONNECTING},
               {"braveVpnPoweredBy", IDS_BRAVE_VPN_POWERED_BY},
               {"braveVpnOptimal",
                IDS_BRAVE_VPN_SERVER_SELECTION_OPTIMAL_LABEL},
               {"braveVpnChangeRegion", IDS_BRAVE_VPN_WIDGET_CHANGE_LABEL},
               {"braveVpnCTA", IDS_BRAVE_VPN_WIDGET_CTA},
               {"braveVpnPurchased", IDS_BRAVE_VPN_HAS_PURCHASED},
#endif

               // Brave Talk  Widget
           }},
          {"adblock",
           {
               {"additionalFiltersTitle", IDS_ADBLOCK_ADDITIONAL_FILTERS_TITLE},
               {"additionalFiltersWarning",
                IDS_ADBLOCK_ADDITIONAL_FILTERS_WARNING},
               {"adsBlocked", IDS_ADBLOCK_TOTAL_ADS_BLOCKED},
               {"customFiltersTitle", IDS_ADBLOCK_CUSTOM_FILTERS_TITLE},
               {"customFiltersInstructions",
                IDS_ADBLOCK_CUSTOM_FILTERS_INSTRUCTIONS},
               {"customListSubscriptionsTitle",
                IDS_ADBLOCK_CUSTOM_LIST_SUBSCRIPTIONS_TITLE},
               {"customListSubscriptionsInstructions",
                IDS_ADBLOCK_CUSTOM_LIST_SUBSCRIPTIONS_INSTRUCTIONS},
               {"customListSubscriptionsDisclaimer",
                IDS_ADBLOCK_CUSTOM_LIST_SUBSCRIPTIONS_DISCLAIMER},

               {"customListSubscriptionsEnterSubscriptionUrlPlaceholder",
                IDS_ADBLOCK_CUSTOM_LIST_SUBSCRIPTIONS_ENTER_SUBSCRIPTION_URL_PLACEHOLDER},
               {"customListSubscriptionsSubmitNewSubscription",
                IDS_ADBLOCK_CUSTOM_LIST_SUBSCRIPTIONS_SUBMIT_NEW_SUBSCRIPTION},
               {"customListSubscriptionsCancelAddSubscription",
                IDS_ADBLOCK_CUSTOM_LIST_SUBSCRIPTIONS_CANCEL_ADD_SUBSCRIPTION},
               {"customListSubscriptionsAddNewFilterList",
                IDS_ADBLOCK_CUSTOM_LIST_SUBSCRIPTIONS_ADD_NEW_FILTER_LIST},
               {"customListSubscriptionsTableFilterListColumn",
                IDS_ADBLOCK_CUSTOM_LIST_SUBSCRIPTIONS_TABLE_FILTER_LIST_COLUMN},
               {"customListSubscriptionsTableLastUpdatedColumn",
                IDS_ADBLOCK_CUSTOM_LIST_SUBSCRIPTIONS_TABLE_LAST_UPDATED_COLUMN},
               {"customListSubscriptionsTriggerUpdate",
                IDS_ADBLOCK_CUSTOM_LIST_SUBSCRIPTIONS_TRIGGER_UPDATE},
               {"customListSubscriptionsViewListSource",
                IDS_ADBLOCK_CUSTOM_LIST_SUBSCRIPTIONS_VIEW_LIST_SOURCE},
               {"customListSubscriptionsUnsubscribe",
                IDS_ADBLOCK_CUSTOM_LIST_SUBSCRIPTIONS_UNSUBSCRIBE},
           }},
          {
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)
              "webcompat",
              {
                  // Report modal
                  {"reportModalTitle",
                   IDS_BRAVE_WEBCOMPATREPORTER_REPORT_MODAL_TITLE},
                  {"reportExplanation",
                   IDS_BRAVE_WEBCOMPATREPORTER_REPORT_EXPLANATION},
                  {"reportNonHttpExplanation",
                   IDS_BRAVE_WEBCOMPATREPORTER_REPORT_NON_HTTP_EXPLANATION},
                  {"reportLocalExplanation",
                   IDS_BRAVE_WEBCOMPATREPORTER_REPORT_LOCAL_EXPLANATION},
                  {"reportErrorPageExplanation",
                   IDS_BRAVE_WEBCOMPATREPORTER_REPORT_ERROR_PAGE_EXPLANATION},
                  {"reportDisclaimer",
                   IDS_BRAVE_WEBCOMPATREPORTER_REPORT_DISCLAIMER2},
                  {"reportInfoLink", IDS_BRAVE_WEBCOMPATREPORTER_INFO_LINK},
                  {"reportDetails", IDS_BRAVE_WEBCOMPATREPORTER_REPORT_DETAILS},
                  {"reportContactPlaceholder",
                   IDS_BRAVE_WEBCOMPATREPORTER_REPORT_CONTACT_PLACEHOLDER},
                  {"reportContactLabel",
                   IDS_BRAVE_WEBCOMPATREPORTER_REPORT_CONTACT_LABEL},
                  {"reportContactPopupInfoLabel",
                   IDS_BRAVE_WEBCOMPATREPORTER_REPORT_CONTACT_INFO_APOPUP_EXPL},
                  {"attachScreenshotLabel",
                   IDS_BRAVE_WEBCOMPATREPORTER_ATTACH_SCREENSHOT_LABEL},
                  {"viewScreenshotLabel",
                   IDS_BRAVE_WEBCOMPATREPORTER_VIEW_SCREENSHOT_LABEL},
                  {"cancel", IDS_BRAVE_WEBCOMPATREPORTER_CANCEL},
                  {"close", IDS_BRAVE_WEBCOMPATREPORTER_CLOSE},
                  {"submit", IDS_BRAVE_WEBCOMPATREPORTER_SUBMIT},
                  // Confirmation modal
                  {"thankYou", IDS_BRAVE_WEBCOMPATREPORTER_THANK_YOU},
                  {"confirmationNotice",
                   IDS_BRAVE_WEBCOMPATREPORTER_CONFIRMATION_NOTICE},
              }
#endif
          },
      }};

  if (auto it = kLocalizedStrings->find(webui_name);
      it != kLocalizedStrings->end()) {
    return it->second;
  }
  return {};
}  // NOLINT (readability/fn_size)

}  // namespace brave
