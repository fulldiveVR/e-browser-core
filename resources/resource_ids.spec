# Since recent changes upstream, Chromium is now using IDs up to ~59570 (see end
# of //out/<BUILD_TYPE>/gen/tools/gritsettings/default_resource_ids). We
# previously added our strings after all of the upstream strings, but we are now
# too close to the maximum id (65536) to continue doing that. Instead, we now
# overlap with a section of upstream strings related to ChromeOS/Ash which are
# unused by us. This range currently runs from [31600-40000), so it should
# provide a decent amount of room for future growth.
{
  "SRCDIR": "../..",
  "brave/common/extensions/api/brave_api_resources.grd": {
    "includes": [31600],
  },
  "brave/components/resources/brave_components_resources.grd": {
    "includes": [31620],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_adblock/brave_adblock.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [31640],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_new_tab/brave_new_tab.grd": {
    "META": {"sizes": {"includes": [50]}},
    "includes": [31660],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_welcome/brave_welcome.grd": {
    "META": {"sizes": {"includes": [20]}},
    "includes": [31680],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/browser/resources/settings/brave_settings_resources.grd": {
    "META": {"sizes": {"includes": [20]}},
    "includes": [31700],
  },
  "brave/app/brave_generated_resources.grd": {
    "includes": [31720],
    "messages": [31740],
  },
  "brave/app/theme/brave_theme_resources.grd": {
    "structures": [31760],
  },
  "brave/app/theme/brave_unscaled_resources.grd": {
    "includes": [31780],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-rewards_internals/rewards_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [31820],
  },
  "brave/components/resources/brave_components_strings.grd": {
    "messages": [31840],
  },
  # This file is generated during the build.
  # This file is generated during the build.
  "brave/components/brave_extension/extension/resources.grd": {
    "includes": [31900],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_extension/brave_extension.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [31920],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-webcompat_reporter/webcompat_reporter.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [31940],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-cosmetic_filters/cosmetic_filters.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [31960],
  },
  # This file is generated during the build.
  # This file is generated during the build.
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_vpn_panel/brave_vpn_panel.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32040],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_shields_panel/brave_shields_panel.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32060],
  },
  # This file is generated during the build.
  # This file is generated during the build.
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_private_new_tab/brave_private_new_tab.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32120],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-playlist/playlist.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32140],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_adblock_internals/brave_adblock_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32220],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-tip_panel/tip_panel.grd": {
    "META": {"sizes": {"includes": [20]}},
    "includes": [32320]
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-ai_chat_ui/ai_chat_ui.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32340],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-skus_internals/skus_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32360],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_news_internals/brave_news_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32380],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-line_chart_display/line_chart_display.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32400]
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-ai_rewriter_ui/ai_rewriter_ui.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32420],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-creator_detection/creator_detection.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32460],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-custom_site_distiller_scripts/custom_site_distiller_scripts.grd": {
    "META": {"sizes": {"includes": [50]}},
    "includes": [32500],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/browser/resources/brave_education/resources.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32520],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-new_tab_takeover/new_tab_takeover.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32540],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_new_tab_page_refresh/brave_new_tab_page_refresh.grd": {
    "META": {"sizes": {"includes": [30]}},
    "includes": [32560],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-email_aliases/email_aliases.grd": {
    "META": {"sizes": {"includes": [40]}},
    "includes": [32580],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/components/brave_account/resources/resources.grd": {
    "META": {"sizes": {"includes": [25]}},
    "includes": [32600],
  },
  "brave/ios/web/test/test_resources.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [32620],
  },
  # WARNING: The upstream ChromeOS/Ash strings currently run through 40000. We
  # must be careful not to exceed that maximum when adding new strings here.
  # Check out/<BUILD_TYPE>/gen/brave/resources/brave_resource_ids for how much
  # the ids got expanded after the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-aiwize_applications/aiwize_applications.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [35000],
  },
  "brave/components/aiwize_agent/resources.grd": {
    "includes": [35040],
  },
}
