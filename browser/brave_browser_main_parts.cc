/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/brave_browser_main_parts.h"

#include <memory>
#include <utility>

#include "base/check.h"
#include "base/command_line.h"
#include "base/path_service.h"
#include "brave/browser/browsing_data/brave_clear_browsing_data.h"
#include "brave/components/brave_component_updater/browser/brave_on_demand_updater.h"
#include "brave/components/brave_sync/features.h"
#include "brave/components/constants/brave_constants.h"
#include "brave/components/constants/pref_names.h"
#include "brave/components/ipfs/buildflags/buildflags.h"
#include "build/build_config.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/chrome_features.h"
#include "chrome/common/chrome_paths.h"
#include "components/component_updater/component_updater_service.h"
#include "components/prefs/pref_service.h"
#include "components/sync/base/command_line_switches.h"
#include "components/sync/service/sync_service.h"
#include "components/sync/service/sync_user_settings.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/web_contents.h"
#include "extensions/buildflags/buildflags.h"
#include "media/base/media_switches.h"



#if !BUILDFLAG(IS_ANDROID)
#include "brave/browser/infobars/brave_confirm_p3a_infobar_delegate.h"
#include "brave/browser/infobars/brave_sync_account_deleted_infobar_delegate.h"
#include "brave/browser/infobars/sync_cannot_run_infobar_delegate.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "components/infobars/content/content_infobar_manager.h"
#else
#include "brave/browser/android/youtube_script_injector/features.h"
#endif

#if BUILDFLAG(DEPRECATE_IPFS)
#include "brave/components/ipfs/ipfs_component_cleaner.h"
#endif  // BUILDFLAG(DEPRECATE_IPFS)

ChromeBrowserMainParts::ChromeBrowserMainParts(bool is_integration_test,
                                               StartupData* startup_data)
    : ChromeBrowserMainParts_ChromiumImpl(is_integration_test, startup_data) {}

ChromeBrowserMainParts::~ChromeBrowserMainParts() = default;

int ChromeBrowserMainParts::PreMainMessageLoopRun() {
  brave_component_updater::BraveOnDemandUpdater::GetInstance()
      ->RegisterOnDemandUpdater(
          &g_browser_process->component_updater()->GetOnDemandUpdater());

  return ChromeBrowserMainParts_ChromiumImpl::PreMainMessageLoopRun();
}

void ChromeBrowserMainParts::PreBrowserStart() {

  ChromeBrowserMainParts_ChromiumImpl::PreBrowserStart();
}

void ChromeBrowserMainParts::PostBrowserStart() {
  ChromeBrowserMainParts_ChromiumImpl::PostBrowserStart();


#if !BUILDFLAG(IS_ANDROID)
  Browser* browser = chrome::FindLastActive();
  content::WebContents* active_web_contents = nullptr;

  if (browser) {
    active_web_contents = browser->tab_strip_model()->GetActiveWebContents();

    if (active_web_contents) {
      Profile* profile =
          Profile::FromBrowserContext(active_web_contents->GetBrowserContext());
      infobars::ContentInfoBarManager* infobar_manager =
          infobars::ContentInfoBarManager::FromWebContents(active_web_contents);
      if (profile && infobar_manager) {
        BraveConfirmP3AInfoBarDelegate::Create(
            infobar_manager, g_browser_process->local_state());
        SyncCannotRunInfoBarDelegate::Create(infobar_manager, profile, browser);

        BraveSyncAccountDeletedInfoBarDelegate::Create(active_web_contents,
                                                       profile, browser);
      }
    }
  }
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(DEPRECATE_IPFS)
  ipfs::CleanupIpfsComponent(
      base::PathService::CheckedGet(chrome::DIR_USER_DATA));
#endif  // BUILDFLAG(DEPRECATE_IPFS)
}

void ChromeBrowserMainParts::PreShutdown() {
  content::BraveClearBrowsingData::ClearOnExit();
  ChromeBrowserMainParts_ChromiumImpl::PreShutdown();
}

void ChromeBrowserMainParts::PreProfileInit() {
  ChromeBrowserMainParts_ChromiumImpl::PreProfileInit();
#if !BUILDFLAG(IS_ANDROID)
  auto* command_line = base::CommandLine::ForCurrentProcess();
  if (!base::FeatureList::IsEnabled(brave_sync::features::kBraveSync)) {
    // Disable sync temporarily
    if (!command_line->HasSwitch(syncer::kDisableSync))
      command_line->AppendSwitch(syncer::kDisableSync);
  } else {
    // Relaunch after flag changes will still have the switch
    // when switching from disabled to enabled
    command_line->RemoveSwitch(syncer::kDisableSync);
  }
#endif
}

void ChromeBrowserMainParts::PostProfileInit(Profile* profile,
                                             bool is_initial_profile) {
  ChromeBrowserMainParts_ChromiumImpl::PostProfileInit(profile,
                                                       is_initial_profile);

#if BUILDFLAG(IS_ANDROID)
  if (base::FeatureList::IsEnabled(
          preferences::features::kBraveBackgroundVideoPlayback) &&
      profile->GetPrefs()->GetBoolean(kBackgroundVideoPlaybackEnabled)) {
    auto* command_line = base::CommandLine::ForCurrentProcess();
    command_line->AppendSwitch(switches::kDisableBackgroundMediaSuspend);
  }
#endif
}
