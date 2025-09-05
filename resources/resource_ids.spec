# Since recent changes upstream, Chromium is now using IDs up to ~59570 (see end
# of //out/Component/gen/tools/gritsettings/default_resource_ids). We previously
# added our strings after all of the upstream strings, but we are now too close
# to the maximum id (65536) to continue doing that. Instead, we now overlap with
# a section of upstream strings related to ChromeOS/Ash which are unused by us.
# This range runs from 29300-36930, so it should provide a decent amount of
# room for future growth.
{
  "SRCDIR": "../..",
  "brave/common/extensions/api/brave_api_resources.grd": {
    "includes": [29580],
  },
  "brave/components/resources/brave_components_resources.grd": {
    "includes": [29600],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_adblock/brave_adblock.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [29670],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_new_tab/brave_new_tab.grd": {
    "META": {"sizes": {"includes": [50]}},
    "includes": [29680],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_welcome/brave_welcome.grd": {
    "META": {"sizes": {"includes": [20]}},
    "includes": [29730],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/browser/resources/settings/brave_settings_resources.grd": {
    "META": {"sizes": {"includes": [20]}},
    "includes": [29750],
  },
  "brave/app/brave_generated_resources.grd": {
    "includes": [29770],
    "messages": [29780],
  },
  "brave/app/theme/brave_theme_resources.grd": {
    "structures": [30200],
  },
  "brave/app/theme/brave_unscaled_resources.grd": {
    "includes": [30300],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-rewards_internals/rewards_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [30340],
  },
  "brave/components/resources/brave_components_strings.grd": {
    "messages": [30370],
  },
  # This file is generated during the build.
  # This file is generated during the build.
  "brave/components/brave_extension/extension/resources.grd": {
    "includes": [33880],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_extension/brave_extension.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [33900],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-webcompat_reporter/webcompat_reporter.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [33910],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-cosmetic_filters/cosmetic_filters.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [33920],
  },
  # This file is generated during the build.
  # This file is generated during the build.
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_vpn_panel/brave_vpn_panel.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [33960],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_shields_panel/brave_shields_panel.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [33970],
  },
  # This file is generated during the build.
  # This file is generated during the build.
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_private_new_tab/brave_private_new_tab.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [34040],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-playlist/playlist.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [34050],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-cookie_list_opt_in/cookie_list_opt_in.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [34080],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_adblock_internals/brave_adblock_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [34100],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-tip_panel/tip_panel.grd": {
    "META": {"sizes": {"includes": [20]}},
    "includes": [34540]
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-ai_chat_ui/ai_chat_ui.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [34560],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-skus_internals/skus_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [34570],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_news_internals/brave_news_internals.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [34580],
  },
  # This file is generated during the build.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-line_chart_display/line_chart_display.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [34590]
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-ai_rewriter_ui/ai_rewriter_ui.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [34600],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-creator_detection/creator_detection.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [34660],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-custom_site_distiller_scripts/custom_site_distiller_scripts.grd": {
    "META": {"sizes": {"includes": [50]}},
    "includes": [34680],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/browser/resources/brave_education/resources.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [34730],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-new_tab_takeover/new_tab_takeover.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [34740],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-brave_new_tab_page_refresh/brave_new_tab_page_refresh.grd": {
    "META": {"sizes": {"includes": [30]}},
    "includes": [34750],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-email_aliases/email_aliases.grd": {
    "META": {"sizes": {"includes": [40]}},
    "includes": [34780],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/components/brave_account/resources/resources.grd": {
    "META": {"sizes": {"includes": [25]}},
    "includes": [34810],
  },
  # WARNING: The upstream ChromeOS/Ash strings currently run through 36930. We
  # must be careful not to exceed that maximum when adding new strings here.
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-aiwize_applications/aiwize_applications.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [35000],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-aiwize_dashboard/aiwize_dashboard.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [35020],
  },
  "brave/components/aiwize_agent/resources.grd": {
    "includes": [35040],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-ai_combiner_chat/ai_combiner_chat.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [35050],
  },
  "<(SHARED_INTERMEDIATE_DIR)/brave/web-ui-ai_combiner_panel/ai_combiner_panel.grd": {
    "META": {"sizes": {"includes": [10]}},
    "includes": [35060],
  },
}
