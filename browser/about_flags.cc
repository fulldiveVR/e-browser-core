/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// This file is included into //chrome/browser/about_flags.cc.

#include <initializer_list>

#include "brave/browser/brave_browser_features.h"
#include "brave/browser/brave_features_internal_names.h"
#include "brave/browser/ui/brave_ui_features.h"
#include "brave/browser/ui/tabs/features.h"
#include "brave/browser/updater/buildflags.h"
#include "brave/components/ai_chat/core/common/features.h"
#include "brave/components/ai_rewriter/common/buildflags/buildflags.h"
#include "brave/components/brave_component_updater/browser/features.h"
#include "brave/components/brave_education/buildflags.h"
#include "brave/components/brave_news/common/features.h"
#include "brave/components/brave_shields/core/common/features.h"
#include "brave/components/brave_vpn/common/buildflags/buildflags.h"
#include "brave/components/containers/buildflags/buildflags.h"
#include "brave/components/de_amp/common/features.h"
#include "brave/components/debounce/core/common/features.h"
#include "brave/components/google_sign_in_permission/features.h"
#include "brave/components/ntp_background_images/browser/features.h"
#include "brave/components/playlist/common/buildflags/buildflags.h"
#include "brave/components/psst/common/features.h"
#include "brave/components/request_otr/common/buildflags/buildflags.h"
#include "brave/components/skus/common/features.h"
#include "brave/components/webcompat/core/common/features.h"
#include "build/build_config.h"
#include "chrome/browser/buildflags.h"
#include "chrome/browser/ui/ui_features.h"
#include "components/content_settings/core/common/features.h"
#include "components/history/core/browser/features.h"
#include "components/omnibox/common/omnibox_features.h"
#include "components/sync/base/command_line_switches.h"
#include "components/translate/core/browser/translate_prefs.h"
#include "components/webui/flags/feature_entry.h"
#include "components/webui/flags/feature_entry_macros.h"
#include "components/webui/flags/flags_state.h"
#include "net/base/features.h"
#include "third_party/blink/public/common/features.h"

#if BUILDFLAG(ENABLE_AI_REWRITER)
#include "brave/components/ai_rewriter/common/features.h"
#endif

#if BUILDFLAG(ENABLE_BRAVE_VPN)
#include "brave/components/brave_vpn/common/features.h"
#endif


#if BUILDFLAG(ENABLE_PLAYLIST)
#include "brave/components/playlist/common/features.h"
#endif

#if BUILDFLAG(ENABLE_REQUEST_OTR)
#include "brave/components/request_otr/common/features.h"
#endif

#if BUILDFLAG(IS_ANDROID)
#include "brave/browser/android/safe_browsing/features.h"
#include "brave/browser/android/youtube_script_injector/features.h"
#else
#include "brave/browser/ui/views/tabs/switches.h"
#include "brave/components/commander/common/features.h"
#include "brave/components/commands/common/features.h"
#endif

#if BUILDFLAG(IS_WIN)
#include "sandbox/policy/features.h"
#endif

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "brave/browser/ui/webui/settings/brave_extensions_manifest_v2_handler.h"
#endif

#if BUILDFLAG(ENABLE_BRAVE_EDUCATION)
#include "brave/components/brave_education/features.h"
#endif

#if BUILDFLAG(ENABLE_CONTAINERS)
#include "brave/components/containers/core/common/features.h"
#endif

#if BUILDFLAG(ENABLE_OMAHA4)
#include "brave/browser/updater/features.h"
#endif

#define EXPAND_FEATURE_ENTRIES(...) __VA_ARGS__,

const flags_ui::FeatureEntry::FeatureParam
    kZCashShieldedTransactionsDisabled[] = {
        {"zcash_shielded_transactions_enabled", "false"}};


const flags_ui::FeatureEntry::FeatureVariation kZCashFeatureVariations[] = {
    {"- Shielded support disabled", kZCashShieldedTransactionsDisabled,
     std::size(kZCashShieldedTransactionsDisabled), nullptr},
};

namespace {
const char* const kBraveSyncImplLink[1] = {"https://github.com/brave/go-sync"};
}


#define REQUEST_OTR_FEATURE_ENTRIES                                           \
  IF_BUILDFLAG(                                                               \
      ENABLE_REQUEST_OTR,                                                     \
      EXPAND_FEATURE_ENTRIES({                                                \
          "aiwize-request-otr-tab",                                            \
          "Enable Request-OTR Tab",                                           \
          "Suggest going off-the-record when visiting potentially sensitive " \
          "URLs",                                                             \
          kOsDesktop | kOsAndroid,                                            \
          FEATURE_VALUE_TYPE(request_otr::features::kBraveRequestOTRTab),     \
      }))

#define BRAVE_MODULE_FILENAME_PATCH                                            \
  IF_BUILDFLAG(                                                                \
      IS_WIN,                                                                  \
      EXPAND_FEATURE_ENTRIES({                                                 \
          "aiwize-module-filename-patch",                                       \
          "Enable Module Filename patch",                                      \
          "Enables patching of executable's name from aiwize.exe to "           \
          "chrome.exe in sandboxed processes.",                                \
          kOsWin,                                                              \
          FEATURE_VALUE_TYPE(sandbox::policy::features::kModuleFileNamePatch), \
      }))

#define BRAVE_WORKAROUND_NEW_WINDOW_FLASH                                  \
  IF_BUILDFLAG(                                                            \
      IS_WIN,                                                              \
      EXPAND_FEATURE_ENTRIES({                                             \
          "aiwize-workaround-new-window-flash",                             \
          "Workaround a white flash on new window creation",               \
          "Enable workaround to prevent new windows being created with a " \
          "white background",                                              \
          kOsWin,                                                          \
          FEATURE_VALUE_TYPE(::features::kBraveWorkaroundNewWindowFlash),  \
      }))



#define BRAVE_NEWS_FEATURE_ENTRIES                                             \
  EXPAND_FEATURE_ENTRIES(                                                      \
      {                                                                        \
          "aiwize-news-peek",                                                   \
          "AI Wize News prompts on New Tab Page",                                \
          "Prompt AI Wize News via the top featured article peeking up from "    \
          "the bottom of the New Tab Page, after a short delay.",              \
          kOsDesktop,                                                          \
          FEATURE_VALUE_TYPE(brave_news::features::kBraveNewsCardPeekFeature), \
      },                                                                       \
      {                                                                        \
          "aiwize-news-feed-update",                                            \
          "AI Wize News Feed Update",                                            \
          "Use the updated AI Wize News feed",                                   \
          kOsDesktop,                                                          \
          FEATURE_VALUE_TYPE(brave_news::features::kBraveNewsFeedUpdate),      \
      })

#define PLAYLIST_FEATURE_ENTRIES                                       \
  IF_BUILDFLAG(                                                        \
      ENABLE_PLAYLIST,                                                 \
      EXPAND_FEATURE_ENTRIES(                                          \
          {                                                            \
              kPlaylistFeatureInternalName,                            \
              "Playlist",                                              \
              "Enables Playlist",                                      \
              kOsMac | kOsWin | kOsLinux | kOsAndroid,                 \
              FEATURE_VALUE_TYPE(playlist::features::kPlaylist),       \
          },                                                           \
          {                                                            \
              kPlaylistFakeUAFeatureInternalName,                      \
              "PlaylistFakeUA",                                        \
              "Use fake UA for playlist",                              \
              kOsMac | kOsWin | kOsLinux | kOsAndroid,                 \
              FEATURE_VALUE_TYPE(playlist::features::kPlaylistFakeUA), \
          }))

#if !BUILDFLAG(IS_ANDROID)
#define BRAVE_COMMANDS_FEATURE_ENTRIES                                      \
  EXPAND_FEATURE_ENTRIES(                                                   \
      {                                                                     \
          "aiwize-commands",                                                 \
          "AI Wize Commands",                                                 \
          "Enable experimental page for viewing and executing commands in " \
          "AI Wize",                                                          \
          kOsWin | kOsMac | kOsLinux,                                       \
          FEATURE_VALUE_TYPE(commands::features::kBraveCommands),           \
      },                                                                    \
      {"aiwize-commands-omnibox", "AI Wize Commands in Omnibox",               \
       "Enable quick commands in the omnibox", kOsWin | kOsMac | kOsLinux,  \
       FEATURE_VALUE_TYPE(features::kBraveCommandsInOmnibox)})
#else
#define BRAVE_COMMANDS_FEATURE_ENTRIES
#endif

#define CONTAINERS_FEATURE_ENTRIES                                             \
  IF_BUILDFLAG(                                                                \
      ENABLE_CONTAINERS,                                                       \
      EXPAND_FEATURE_ENTRIES({                                                 \
          "containers",                                                        \
          "Enable Containers",                                                 \
          "Allows websites to be opened in contained tabs, keeping different " \
          "identities separate within the same browser profile",               \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(containers::features::kContainers),               \
      }))

#if BUILDFLAG(IS_LINUX)
#define BRAVE_CHANGE_ACTIVE_TAB_ON_SCROLL_EVENT_FEATURE_ENTRIES               \
  EXPAND_FEATURE_ENTRIES({                                                    \
      "aiwize-change-active-tab-on-scroll-event",                              \
      "Change active tab on scroll event",                                    \
      "Change the active tab when scroll events occur on tab strip.",         \
      kOsLinux,                                                               \
      FEATURE_VALUE_TYPE(tabs::features::kBraveChangeActiveTabOnScrollEvent), \
  })
#else
#define BRAVE_CHANGE_ACTIVE_TAB_ON_SCROLL_EVENT_FEATURE_ENTRIES
#endif

#if BUILDFLAG(IS_ANDROID)
#define BRAVE_BACKGROUND_VIDEO_PLAYBACK_ANDROID                                \
  EXPAND_FEATURE_ENTRIES({                                                     \
      "aiwize-background-video-playback",                                       \
      "Background video playback",                                             \
      "Enables play audio from video in background when tab is not active or " \
      "device screen is turned off.",                                          \
      kOsAndroid,                                                              \
      FEATURE_VALUE_TYPE(                                                      \
          preferences::features::kBraveBackgroundVideoPlayback),               \
  })
#define BRAVE_SAFE_BROWSING_ANDROID                                           \
  EXPAND_FEATURE_ENTRIES({                                                    \
      "aiwize-safe-browsing",                                                  \
      "Safe Browsing",                                                        \
      "Enables Google Safe Browsing for determining whether a URL has been "  \
      "marked as a known threat.",                                            \
      kOsAndroid,                                                             \
      FEATURE_VALUE_TYPE(safe_browsing::features::kBraveAndroidSafeBrowsing), \
  })
#else
#define BRAVE_BACKGROUND_VIDEO_PLAYBACK_ANDROID
#define BRAVE_SAFE_BROWSING_ANDROID
#endif  // BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
constexpr flags_ui::FeatureEntry::Choice kVerticalTabExpandDelayChoices[] = {
    {"default", "", ""},
    {"0ms", tabs::switches::kVerticalTabExpandDelaySwitch, "0"},
    {"50ms", tabs::switches::kVerticalTabExpandDelaySwitch, "50"},
    {"100ms", tabs::switches::kVerticalTabExpandDelaySwitch, "100"},
    {"150ms", tabs::switches::kVerticalTabExpandDelaySwitch, "150"},
    {"200ms", tabs::switches::kVerticalTabExpandDelaySwitch, "200"},
    {"250ms", tabs::switches::kVerticalTabExpandDelaySwitch, "250"},
    {"300ms", tabs::switches::kVerticalTabExpandDelaySwitch, "300"},
    {"400ms", tabs::switches::kVerticalTabExpandDelaySwitch, "400"},
};

constexpr flags_ui::FeatureEntry::Choice kVerticalTabCollapseDelayChoices[] = {
    {"default", "", ""},
    {"0ms", tabs::switches::kVerticalTabCollapseDelaySwitch, "0"},
    {"50ms", tabs::switches::kVerticalTabCollapseDelaySwitch, "50"},
    {"100ms", tabs::switches::kVerticalTabCollapseDelaySwitch, "100"},
    {"150ms", tabs::switches::kVerticalTabCollapseDelaySwitch, "150"},
    {"200ms", tabs::switches::kVerticalTabCollapseDelaySwitch, "200"},
    {"250ms", tabs::switches::kVerticalTabCollapseDelaySwitch, "250"},
    {"300ms", tabs::switches::kVerticalTabCollapseDelaySwitch, "300"},
    {"400ms", tabs::switches::kVerticalTabCollapseDelaySwitch, "400"},
};

#define BRAVE_TABS_FEATURE_ENTRIES                                             \
  EXPAND_FEATURE_ENTRIES(                                                      \
      {                                                                        \
          "aiwize-shared-pinned-tabs",                                          \
          "Shared pinned tab",                                                 \
          "Pinned tabs are shared across windows",                             \
          kOsWin | kOsMac | kOsLinux,                                          \
          FEATURE_VALUE_TYPE(tabs::features::kBraveSharedPinnedTabs),          \
      },                                                                       \
      {                                                                        \
          "aiwize-horizontal-tabs-update",                                      \
          "Updated horizontal tabs design",                                    \
          "Updates the look and feel or horizontal tabs",                      \
          kOsWin | kOsMac | kOsLinux,                                          \
          FEATURE_VALUE_TYPE(tabs::features::kBraveHorizontalTabsUpdate),      \
      },                                                                       \
      {                                                                        \
          "aiwize-compact-horizontal-tabs",                                     \
          "Compact horizontal tabs design",                                    \
          "Reduces the height of horizontal tabs",                             \
          kOsWin | kOsMac | kOsLinux,                                          \
          FEATURE_VALUE_TYPE(tabs::features::kBraveCompactHorizontalTabs),     \
      },                                                                       \
      {                                                                        \
          "aiwize-vertical-tab-scroll-bar",                                     \
          "Show scroll bar on vertical tab strip",                             \
          "Shows scroll bar on vertical tab strip when it overflows",          \
          kOsWin | kOsMac | kOsLinux,                                          \
          FEATURE_VALUE_TYPE(tabs::features::kBraveVerticalTabScrollBar),      \
      },                                                                       \
      {                                                                        \
          "aiwize-vertical-tab-hide-completely",                                \
          "AI Wize Vertical Tab Hide Completely",                                \
          "Hides the vertical tab strip when collapsed",                       \
          kOsWin | kOsMac | kOsLinux,                                          \
          FEATURE_VALUE_TYPE(tabs::features::kBraveVerticalTabHideCompletely), \
      },                                                                       \
      {                                                                        \
          "aiwize-vertical-tab-expand-delay",                                   \
          "AI Wize Vertical Tab Expand Delay",                                   \
          "Delay before expanding the vertical tab strip when hovering",       \
          kOsWin | kOsMac | kOsLinux,                                          \
          MULTI_VALUE_TYPE(kVerticalTabExpandDelayChoices),                    \
      },                                                                       \
      {                                                                        \
          "aiwize-vertical-tab-collapse-delay",                                 \
          "AI Wize Vertical Tab Collapse Delay",                                 \
          "Delay before collapsing the vertical tab strip when mouse exits",   \
          kOsWin | kOsMac | kOsLinux,                                          \
          MULTI_VALUE_TYPE(kVerticalTabCollapseDelayChoices),                  \
      },                                                                       \
      {                                                                        \
          "aiwize-tree-tab",                                                    \
          "AI Wize Tree Tab",                                                    \
          "Enables the Tree Tab feature",                                      \
          kOsWin | kOsMac | kOsLinux,                                          \
          FEATURE_VALUE_TYPE(tabs::features::kBraveTreeTab),                   \
      })
#else
#define BRAVE_TABS_FEATURE_ENTRIES
#endif

#if BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
#define BRAVE_MIDDLE_CLICK_AUTOSCROLL_FEATURE_ENTRY                      \
  EXPAND_FEATURE_ENTRIES({                                               \
      "middle-button-autoscroll",                                        \
      "Middle button autoscroll",                                        \
      "Enables autoscrolling when the middle mouse button is clicked",   \
      kOsMac | kOsLinux,                                                 \
      FEATURE_VALUE_TYPE(blink::features::kMiddleButtonClickAutoscroll), \
  })
#else
#define BRAVE_MIDDLE_CLICK_AUTOSCROLL_FEATURE_ENTRY
#endif

#define BRAVE_AI_CHAT_FEATURE_ENTRIES                                          \
  EXPAND_FEATURE_ENTRIES(                                                      \
      {                                                                        \
          "aiwize-ai-chat",                                                     \
          "AI Wize AI Chat",                                                     \
          "Summarize articles and engage in conversation with AI",             \
          kOsWin | kOsMac | kOsLinux | kOsAndroid,                             \
          FEATURE_VALUE_TYPE(ai_chat::features::kAIChat),                      \
      },                                                                       \
      {                                                                        \
          "aiwize-ai-first",                                                    \
          "AI Wize AI Chat First",                                               \
          "Prioritize Leo vs Search within AI Wize",                             \
          kOsWin | kOsMac | kOsLinux | kOsAndroid,                             \
          FEATURE_VALUE_TYPE(ai_chat::features::kAIChatFirst),                 \
      },                                                                       \
      {                                                                        \
          "aiwize-ai-chat-history",                                             \
          "AI Wize AI Chat History",                                             \
          "Enables AI Chat History persistence and management",                \
          kOsWin | kOsMac | kOsLinux | kOsAndroid,                             \
          FEATURE_VALUE_TYPE(ai_chat::features::kAIChatHistory),               \
      },                                                                       \
      {                                                                        \
          "aiwize-ai-host-specific-distillation",                               \
          "AI Wize AI Host-Specific Distillation",                               \
          "Enables support for host-specific distillation scripts",            \
          kOsWin | kOsMac | kOsLinux | kOsAndroid,                             \
          FEATURE_VALUE_TYPE(ai_chat::features::kCustomSiteDistillerScripts),  \
      },                                                                       \
      {                                                                        \
          "aiwize-ai-chat-context-menu-rewrite-in-place",                       \
          "AI Wize AI Chat Rewrite In Place From Context Menu",                  \
          "Enables AI Chat rewrite in place feature from the context menu",    \
          kOsDesktop,                                                          \
          FEATURE_VALUE_TYPE(ai_chat::features::kContextMenuRewriteInPlace),   \
      },                                                                       \
      {                                                                        \
          "aiwize-ai-chat-allow-private-ips",                                   \
          "Private IP Addresses for Custom Model Endpoints",                   \
          "Permits the use of private IP addresses as model endpoint URLs",    \
          kOsWin | kOsMac | kOsLinux | kOsAndroid,                             \
          FEATURE_VALUE_TYPE(ai_chat::features::kAllowPrivateIPs),             \
      },                                                                       \
      {                                                                        \
          "aiwize-ai-chat-open-leo-from-aiwize-search",                          \
          "Open AI Wize Chat from AI Wize Search",                                \
          "Enables opening AI Wize Chat from AI Wize Search",                     \
          kOsDesktop | kOsAndroid,                                             \
          FEATURE_VALUE_TYPE(ai_chat::features::kOpenAIChatFromBraveSearch),   \
      },                                                                       \
      {                                                                        \
          "aiwize-ai-chat-web-content-association-default",                     \
          "AI Wize AI Chat Web Content Association Default",                     \
          "For AI Chat Conversations which are associated with web content, "  \
          "allow the toggle for sending page content to be set to enabled "    \
          "when the conversation is created.",                                 \
          kOsWin | kOsMac | kOsLinux | kOsAndroid,                             \
          FEATURE_VALUE_TYPE(ai_chat::features::kPageContextEnabledInitially), \
      })

#if BUILDFLAG(ENABLE_AI_REWRITER)
#define BRAVE_AI_REWRITER                                     \
  EXPAND_FEATURE_ENTRIES({                                    \
      "aiwize-ai-rewriter",                                    \
      "AI Wize AI Rewriter",                                    \
      "Enables the AI Wize AI rewriter dialog",                 \
      kOsWin | kOsMac | kOsLinux,                             \
      FEATURE_VALUE_TYPE(ai_rewriter::features::kAIRewriter), \
  })
#else
#define BRAVE_AI_REWRITER
#endif

#define BRAVE_OMNIBOX_FEATURES                                                \
  EXPAND_FEATURE_ENTRIES(                                                     \
      {                                                                       \
          "aiwize-omnibox-tab-switch-by-default",                              \
          "AI Wize Tab Switch by Default",                                      \
          "Prefer switching to already open tabs, rather than navigating in " \
          "a "                                                                \
          "new tab",                                                          \
          kOsWin | kOsLinux | kOsMac,                                         \
          FEATURE_VALUE_TYPE(omnibox::kOmniboxTabSwitchByDefault),            \
      },                                                                      \
      {                                                                       \
          "aiwize-history-more-search-results",                                \
          "AI Wize More History",                                               \
          "Include more history in the omnibox search results",               \
          kOsWin | kOsLinux | kOsMac | kOsAndroid,                            \
          FEATURE_VALUE_TYPE(history::kHistoryMoreSearchResults),             \
      })

#define BRAVE_EXTENSIONS_MANIFEST_V2                                        \
  IF_BUILDFLAG(ENABLE_EXTENSIONS,                                           \
               EXPAND_FEATURE_ENTRIES({                                     \
                   "aiwize-extensions-manifest-v2",                          \
                   "AI Wize Extensions manifest V2",                          \
                   "Enables AI Wize support for some manifest V2 extensions", \
                   kOsDesktop,                                              \
                   FEATURE_VALUE_TYPE(kExtensionsManifestV2),               \
               }))

#define BRAVE_ADBLOCK_CUSTOM_SCRIPTLETS                                 \
  EXPAND_FEATURE_ENTRIES({                                              \
      "aiwize-adblock-custom-scriptlets",                                \
      "AI Wize Adblock Custom Scriptlets",                                \
      "Allows adding custom scriptlets from settings",                  \
      kOsDesktop | kOsAndroid,                                          \
      FEATURE_VALUE_TYPE(                                               \
          brave_shields::features::kCosmeticFilteringCustomScriptlets), \
  })

#if BUILDFLAG(ENABLE_BRAVE_EDUCATION)
#define BRAVE_EDUCATION_FEATURE_ENTRIES                                       \
  EXPAND_FEATURE_ENTRIES({                                                    \
      "aiwize-show-getting-started-page",                                      \
      "Show getting started pages",                                           \
      "Show a getting started page after completing the Welcome UX.",         \
      kOsDesktop,                                                             \
      FEATURE_VALUE_TYPE(brave_education::features::kShowGettingStartedPage), \
  })
#else
#define BRAVE_EDUCATION_FEATURE_ENTRIES
#endif

#if BUILDFLAG(ENABLE_OMAHA4)
#define BRAVE_UPDATER_FEATURE_ENTRIES                          \
  EXPAND_FEATURE_ENTRIES({                                     \
      "aiwize-use-omaha4-alpha",                                \
      "Use Omaha 4 Alpha",                                     \
      "Use the new automatic update system",                   \
      kOsMac,                                                  \
      FEATURE_VALUE_TYPE(brave_updater::kBraveUseOmaha4Alpha), \
  })
#else
#define BRAVE_UPDATER_FEATURE_ENTRIES
#endif

// Keep the last item empty.
#define LAST_BRAVE_FEATURE_ENTRIES_ITEM

#define BRAVE_ABOUT_FLAGS_FEATURE_ENTRIES                                      \
  EXPAND_FEATURE_ENTRIES(                                                      \
      {                                                                        \
          "use-dev-updater-url",                                               \
          "Use dev updater url",                                               \
          "Use the dev url for the component updater. This is for internal "   \
          "testing only.",                                                     \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(brave_component_updater::kUseDevUpdaterUrl),      \
      },                                                                       \
      {                                                                        \
          "aiwize-ntp-branded-wallpaper-demo",                                  \
          "New Tab Page Demo Branded Wallpaper",                               \
          "Force dummy data for the Branded Wallpaper New Tab Page "           \
          "Experience. View rate and user opt-in conditionals will still be "  \
          "followed to decide when to display the Branded Wallpaper.",         \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              ntp_background_images::features::kBraveNTPBrandedWallpaperDemo), \
      },                                                                       \
      {                                                                        \
          "aiwize-ntp-search-widget",                                           \
          "AI Wize Search Widget on the NTP",                                    \
          "Enables searching directly from the New Tab Page",                  \
          kOsDesktop,                                                          \
          FEATURE_VALUE_TYPE(features::kBraveNtpSearchWidget),                 \
      },                                                                       \
      {                                                                        \
          "aiwize-ntp-refresh-enabled",                                         \
          "New Tab Page refresh",                                              \
          "Enables the refreshed version of the New Tab Page",                 \
          kOsDesktop,                                                          \
          FEATURE_VALUE_TYPE(features::kBraveNewTabPageRefreshEnabled),        \
      },                                                                       \
      {                                                                        \
          "aiwize-adblock-cname-uncloaking",                                    \
          "Enable CNAME uncloaking",                                           \
          "Take DNS CNAME records into account when making network request "   \
          "blocking decisions.",                                               \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kBraveAdblockCnameUncloaking),          \
      },                                                                       \
      {                                                                        \
          "aiwize-adblock-collapse-blocked-elements",                           \
          "Collapse HTML elements with blocked source attributes",             \
          "Cause iframe and img elements to be collapsed if the URL of their " \
          "src attribute is blocked",                                          \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kBraveAdblockCollapseBlockedElements),  \
      },                                                                       \
      {                                                                        \
          "aiwize-adblock-cookie-list-default",                                 \
          "Treat 'Easylist-Cookie List' as a default list source",             \
          "Enables the 'Easylist-Cookie List' regional list if its toggle in " \
          "aiwize://adblock hasn't otherwise been modified",                    \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kBraveAdblockCookieListDefault),        \
      },                                                                       \
      {                                                                        \
          "aiwize-adblock-cookie-list-opt-in",                                  \
          "Show an opt-in bubble for the 'Easylist-Cookie List' filter",       \
          "When enabled, a bubble will be displayed inviting the user to "     \
          "enable the 'Easylist-Cookie List' filter for blocking cookie "      \
          "consent dialogs",                                                   \
          kOsDesktop | kOsAndroid,                                             \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kBraveAdblockCookieListOptIn),          \
      },                                                                       \
      {                                                                        \
          "aiwize-adblock-cosmetic-filtering",                                  \
          "Enable cosmetic filtering",                                         \
          "Enable support for cosmetic filtering",                             \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kBraveAdblockCosmeticFiltering),        \
      },                                                                       \
      {                                                                        \
          "aiwize-adblock-csp-rules",                                           \
          "Enable support for CSP rules",                                      \
          "Applies additional CSP rules to pages for which a $csp rule has "   \
          "been loaded from a filter list",                                    \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(brave_shields::features::kBraveAdblockCspRules),  \
      },                                                                       \
      {                                                                        \
          "aiwize-adblock-default-1p-blocking",                                 \
          "Shields first-party network blocking",                              \
          "Allow AI Wize Shields to block first-party network requests in "      \
          "Standard blocking mode",                                            \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kBraveAdblockDefault1pBlocking),        \
      },                                                                       \
      {                                                                        \
          "aiwize-adblock-mobile-notifications-list-default",                   \
          "Treat 'Fanboy's Mobile Notifications List' as a default list "      \
          "source",                                                            \
                                                                               \
          "Enables the 'Fanboy's Mobile Notifications List' regional list if " \
          "its toggle in aiwize://adblock hasn't otherwise been modified",      \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(brave_shields::features::                         \
                                 kBraveAdblockMobileNotificationsListDefault), \
      },                                                                       \
      {                                                                        \
          "aiwize-adblock-procedural-filtering",                                \
          "Enable procedural filtering",                                       \
          "Enable support for procedural cosmetic filtering",                  \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kBraveAdblockProceduralFiltering),      \
      },                                                                       \
      {                                                                        \
          "aiwize-adblock-experimental-list-default",                           \
          "Treat 'AI Wize Experimental Adblock Rules' as a default list "        \
          "source",                                                            \
                                                                               \
          "Enables the 'AI Wize Experimental Adblock Rules' regional list if "   \
          "its toggle in aiwize://adblock hasn't otherwise been modified",      \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kBraveAdblockExperimentalListDefault),  \
      },                                                                       \
      {                                                                        \
          "aiwize-adblock-scriptlet-debug-logs",                                \
          "Enable debug logging for scriptlet injections",                     \
          "Enable console debugging for scriptlets injected by cosmetic "      \
          "filtering, exposing additional information that can be useful for " \
          "filter authors.",                                                   \
          kOsDesktop,                                                          \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kBraveAdblockScriptletDebugLogs),       \
      },                                                                       \
      {                                                                        \
          "aiwize-dark-mode-block",                                             \
          "Enable dark mode blocking fingerprinting protection",               \
          "Always report light mode when fingerprinting protections set to "   \
          "Strict",                                                            \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(brave_shields::features::kBraveDarkModeBlock),    \
      },                                                                       \
      {                                                                        \
          "aiwize-domain-block",                                                \
          "Enable domain blocking",                                            \
          "Enable support for blocking domains with an interstitial page",     \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(brave_shields::features::kBraveDomainBlock),      \
      },                                                                       \
      {                                                                        \
          "aiwize-domain-block-1pes",                                           \
          "Enable domain blocking using First Party Ephemeral Storage",        \
          "When visiting a blocked domain, AI Wize will try to enable "          \
          "Ephemeral Storage for a first party context, meaning neither "      \
          "cookies nor localStorage data will be persisted after a website "   \
          "is closed. Ephemeral Storage will be auto-enabled only if no data " \
          "was previously stored for a website",                               \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(brave_shields::features::kBraveDomainBlock1PES),  \
      },                                                                       \
      {                                                                        \
          "aiwize-debounce",                                                    \
          "Enable debouncing",                                                 \
          "Enable support for skipping top-level redirect tracking URLs",      \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(debounce::features::kBraveDebounce),              \
      },                                                                       \
      {                                                                        \
          "aiwize-de-amp",                                                      \
          "Enable De-AMP",                                                     \
          "Enable De-AMPing feature",                                          \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(de_amp::features::kBraveDeAMP),                   \
      },                                                                       \
      {                                                                        \
          "aiwize-google-sign-in-permission",                                   \
          "Enable Google Sign-In Permission Prompt",                           \
          "Enable permissioning access to legacy Google Sign-In",              \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(google_sign_in_permission::features::             \
                                 kBraveGoogleSignInPermission),                \
      },                                                                       \
      {                                                                        \
          "aiwize-localhost-access-permission",                                 \
          "Enable Localhost access permission prompt",                         \
          "Enable permissioning access to localhost connections",              \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kBraveLocalhostAccessPermission),       \
      },                                                                       \
      {                                                                        \
          "aiwize-psst",                                                        \
          "Enable PSST (Privacy Site Settings Tool) feature",                  \
          "Enable PSST feature",                                               \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(psst::features::kBravePsst),                      \
      },                                                                       \
      {                                                                        \
          "aiwize-extension-network-blocking",                                  \
          "Enable extension network blocking",                                 \
          "Enable blocking for network requests initiated by extensions",      \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kBraveExtensionNetworkBlocking),        \
      },                                                                       \
      {                                                                        \
          "aiwize-reduce-language",                                             \
          "Reduce language identifiability",                                   \
          "Reduce the identifiability of my language preferences",             \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(brave_shields::features::kBraveReduceLanguage),   \
      },                                                                       \
      {                                                                        \
          "aiwize-cosmetic-filtering-sync-load",                                \
          "Enable sync loading of cosmetic filter rules",                      \
          "Enable sync loading of cosmetic filter rules",                      \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kCosmeticFilteringSyncLoad),            \
      },                                                                       \
      {                                                                        \
          "block-all-cookies-toggle",                                          \
          "'Block all cookies' option in Shields global defaults",             \
          "Shows the 'Block all cookies' toggle in Shields global defaults. "  \
          "This global setting prevents all websites from storing cookies "    \
          "on your device, but is also very likely to lead to site breakage.", \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(brave_shields::features::kBlockAllCookiesToggle), \
      },                                                                       \
      {                                                                        \
          "block-element-feature",                                             \
          "Enable Block Element feature",                                      \
          "Allows to block selected HTML element on the page",                 \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kBraveShieldsElementPicker),            \
      },                                                                       \
      {                                                                        \
          "aiwize-super-referral",                                              \
          "Enable AI Wize Super Referral",                                       \
          "Use custom theme for AI Wize Super Referral",                         \
          flags_ui::kOsMac | flags_ui::kOsWin | flags_ui::kOsAndroid,          \
          FEATURE_VALUE_TYPE(ntp_background_images::features::                 \
                                 kBraveNTPSuperReferralWallpaper),             \
      },                                                                       \
      {                                                                        \
          "aiwize-ephemeral-storage",                                           \
          "Enable Ephemeral Storage",                                          \
          "Use ephemeral storage for third-party frames",                      \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(net::features::kBraveEphemeralStorage),           \
      },                                                                       \
      {                                                                        \
          "aiwize-ephemeral-storage-keep-alive",                                \
          "Ephemeral Storage Keep Alive",                                      \
          "Keep ephemeral storage partitions alive for a specified time "      \
          "after all tabs for that origin are closed",                         \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(net::features::kBraveEphemeralStorageKeepAlive),  \
      },                                                                       \
      {                                                                        \
          "aiwize-first-party-ephemeral-storage",                               \
          "Enable First Party Ephemeral Storage",                              \
          "Enable support for First Party Ephemeral Storage using "            \
          "SESSION_ONLY cookie setting",                                       \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(net::features::kBraveFirstPartyEphemeralStorage), \
      },                                                                       \
      {                                                                        \
          "aiwize-forget-first-party-storage",                                  \
          "Enable First Party Storage Cleanup support",                        \
          "Add cookie blocking mode which allows AI Wize to cleanup first "      \
          "party storage (Cookies, DOM Storage) on website close",             \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(net::features::kBraveForgetFirstPartyStorage),    \
      },                                                                       \
      {                                                                        \
          "file-system-access-api",                                            \
          "File System Access API",                                            \
          "Enables the File System Access API, giving websites access to the " \
          "file system",                                                       \
          kOsDesktop,                                                          \
          FEATURE_VALUE_TYPE(blink::features::kFileSystemAccessAPI),           \
      },                                                                       \
      {                                                                        \
          "aiwize-web-bluetooth-api",                                           \
          "Web Bluetooth API",                                                 \
          "Enables the Web Bluetooth API, giving websites access to "          \
          "Bluetooth devices",                                                 \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(blink::features::kBraveWebBluetoothAPI),          \
      },                                                                       \
      {                                                                        \
          "navigator-connection-attribute",                                    \
          "Enable navigator.connection attribute",                             \
          "Enables the navigator.connection API. Enabling this API will "      \
          "allow sites to learn information about your network and internet "  \
          "connection. Trackers can use this information to fingerprint your " \
          "browser, or to infer when you are traveling or at home.",           \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(blink::features::kNavigatorConnectionAttribute),  \
      },                                                                       \
      {                                                                        \
          "restrict-websockets-pool",                                          \
          "Restrict WebSockets pool",                                          \
          "Limits simultaneous active WebSockets connections per eTLD+1",      \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(blink::features::kRestrictWebSocketsPool),        \
      },                                                                       \
      {                                                                        \
          "allow-incognito-permission-inheritance",                            \
          "Allow permission inheritance in incognito profiles",                \
          "When enabled, most permissions set in a normal profile will be "    \
          "inherited in incognito profile if they are less permissive, for "   \
          "ex. Geolocation BLOCK will be automatically set to BLOCK in "       \
          "incognito.",                                                        \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              content_settings::kAllowIncognitoPermissionInheritance),         \
      },                                                                       \
      {                                                                        \
          "aiwize-block-screen-fingerprinting",                                 \
          "Block screen fingerprinting",                                       \
          "Prevents JavaScript and CSS from learning the user's screen "       \
          "dimensions or window position.",                                    \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              blink::features::kBraveBlockScreenFingerprinting),               \
      },                                                                       \
      {                                                                        \
          "aiwize-round-time-stamps",                                           \
          "Round time stamps",                                                 \
          "Prevents JavaScript from getting access to high-resolution clocks " \
          "by rounding all DOMHighResTimeStamps to the nearest millisecond.",  \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(blink::features::kBraveRoundTimeStamps),          \
      },                                                                       \
      {                                                                        \
          "restrict-event-source-pool",                                        \
          "Restrict Event Source Pool",                                        \
          "Limits simultaneous active WebSockets connections per eTLD+1",      \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(blink::features::kRestrictEventSourcePool),       \
      },                                                                       \
      {                                                                        \
          "aiwize-copy-clean-link-by-default",                                  \
          "Override default copy hotkey with copy clean link",                 \
          "Sanitize url before copying, replaces default ctrl+c hotkey for "   \
          "url ",                                                              \
          kOsWin | kOsLinux | kOsMac,                                          \
          FEATURE_VALUE_TYPE(features::kBraveCopyCleanLinkByDefault),          \
      },                                                                       \
      {                                                                        \
          "aiwize-clean-link-js-api",                                           \
          "Sanitize URLs in the clipboard",                                    \
          "Sanitize URLs in the clipboard when they are added via the JS API " \
          "(share/copy buttons). ",                                            \
          kOsWin | kOsLinux | kOsMac,                                          \
          FEATURE_VALUE_TYPE(features::kBraveCopyCleanLinkFromJs),             \
      },                                                                       \
      {                                                                        \
          "aiwize-global-privacy-control-enabled",                              \
          "Enable Global Privacy Control",                                     \
          "Enable the Sec-GPC request header and the "                         \
          "navigator.globalPrivacyControl JS API",                             \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(blink::features::kBraveGlobalPrivacyControl),     \
      },                                                                       \
      {                                                                        \
          "https-by-default",                                                  \
          "Use HTTPS by Default",                                              \
          "Attempt to connect to all websites using HTTPS before falling "     \
          "back to HTTP.",                                                     \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(net::features::kBraveHttpsByDefault),             \
      },                                                                       \
      {                                                                        \
          "fallback-dns-over-https",                                           \
          "Use a fallback DoH provider",                                       \
          "In Automatic DoH mode, use a fallback DoH provider if the current " \
          "provider doesn't offer Secure DNS.",                                \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(net::features::kBraveFallbackDoHProvider),        \
      },                                                                       \
      {                                                                        \
          "aiwize-show-strict-fingerprinting-mode",                             \
          "Show Strict Fingerprinting Mode",                                   \
          "Show Strict (aggressive) option for Fingerprinting Mode in "        \
          "AI Wize Shields ",                                                    \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              brave_shields::features::kBraveShowStrictFingerprintingMode),    \
      },                                                                       \
      {                                                                        \
          "aiwize-override-download-danger-level",                              \
          "Override download danger level",                                    \
          "Disables download warnings for files which are considered "         \
          "dangerous when Safe Browsing is disabled. Use at your own risks. "  \
          "Not recommended.",                                                  \
          kOsWin | kOsLinux | kOsMac,                                          \
          FEATURE_VALUE_TYPE(features::kBraveOverrideDownloadDangerLevel),     \
      },                                                                       \
      {                                                                        \
          "aiwize-webcompat-exceptions-service",                                \
          "Allow feature exceptions for webcompat",                            \
          "Disables AI Wize features for specific websites when they break "     \
          "website functionality.",                                            \
          kOsAll,                                                              \
          FEATURE_VALUE_TYPE(                                                  \
              webcompat::features::kBraveWebcompatExceptionsService),          \
      },                                                                       \
      {                                                                        \
          "aiwize-web-view-rounded-corners",                                    \
          "Use rounded corners on main content areas",                         \
          "Renders the main content area and sidebar panel with rounded "      \
          "corners, padding, and a drop shadow",                               \
          kOsWin | kOsLinux | kOsMac,                                          \
          FEATURE_VALUE_TYPE(features::kBraveWebViewRoundedCorners),           \
      },                                                                       \
      {                                                                        \
          "aiwize-override-sync-server-url",                                    \
          "Override AI Wize Sync server URL",                                    \
          "Allows you to use a self-hosted server with Brave Sync. You can "   \
          "learn more about the server implementation in the repository link " \
          "mentioned below. "                                                  \
          "Note: Only HTTPS URLs are supported by default. HTTP URLs are "     \
          "only allowed for potentially trustworthy origins like localhost."   \
          "Insecure URLs that don't meet these requirements will be ignored"   \
          "in favor of the official AI Wize-hosted server",                      \
          kOsAll,                                                              \
          ORIGIN_LIST_VALUE_TYPE(syncer::kSyncServiceURL, ""),                 \
          kBraveSyncImplLink,                                                  \
      })                                                                       \
  BRAVE_NEWS_FEATURE_ENTRIES                                                   \
  REQUEST_OTR_FEATURE_ENTRIES                                                  \
  BRAVE_MODULE_FILENAME_PATCH                                                  \
  PLAYLIST_FEATURE_ENTRIES                                                     \
  BRAVE_COMMANDS_FEATURE_ENTRIES                                               \
  CONTAINERS_FEATURE_ENTRIES                                                   \
  BRAVE_BACKGROUND_VIDEO_PLAYBACK_ANDROID                                      \
  BRAVE_SAFE_BROWSING_ANDROID                                                  \
  BRAVE_CHANGE_ACTIVE_TAB_ON_SCROLL_EVENT_FEATURE_ENTRIES                      \
  BRAVE_TABS_FEATURE_ENTRIES                                                   \
  BRAVE_AI_CHAT_FEATURE_ENTRIES                                                \
  BRAVE_AI_REWRITER                                                            \
  BRAVE_OMNIBOX_FEATURES                                                       \
  BRAVE_MIDDLE_CLICK_AUTOSCROLL_FEATURE_ENTRY                                  \
  BRAVE_EXTENSIONS_MANIFEST_V2                                                 \
  BRAVE_WORKAROUND_NEW_WINDOW_FLASH                                            \
  BRAVE_ADBLOCK_CUSTOM_SCRIPTLETS                                              \
  BRAVE_EDUCATION_FEATURE_ENTRIES                                              \
  BRAVE_UPDATER_FEATURE_ENTRIES                                                \
  LAST_BRAVE_FEATURE_ENTRIES_ITEM  // Keep it as the last item.
namespace flags_ui {
namespace {

// Unused function to reference Brave feature entries for clang
// checks.
[[maybe_unused]] void UseBraveAboutFlags() {
  // These vars are declared in anonymous namespace in
  // //chrome/browser/about_flags.cc. We declare them here
  // manually to instantiate BRAVE_ABOUT_FLAGS_FEATURE_ENTRIES
  // without errors.
  constexpr int kOsAll = 0;
  constexpr int kOsDesktop = 0;

  static_assert(
      std::initializer_list<FeatureEntry>{BRAVE_ABOUT_FLAGS_FEATURE_ENTRIES}
          .size());
}  // namespace

}  // namespace
}  // namespace flags_ui
