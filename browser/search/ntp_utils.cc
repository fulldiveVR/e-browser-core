/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/search/ntp_utils.h"

#include "base/logging.h"
#include "brave/browser/profiles/profile_util.h"
#include "brave/components/constants/pref_names.h"
#include "chrome/browser/ui/webui/new_tab_page/ntp_pref_names.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace {

void ClearNewTabPageProfilePrefs(PrefService* prefs) {
  prefs->ClearPref(kNewTabPageShowTopSites);
}

}  // namespace

namespace new_tab_page {

void MigrateNewTabPagePrefs(PrefService* prefs) {
  // Migrate over to the Chromium setting for shortcuts visible
  // Only sets the value if user has changed it
  const PrefService::Preference* top_sites_pref =
      prefs->FindPreference(kNewTabPageShowTopSites);
  if (top_sites_pref->HasUserSetting()) {
    prefs->SetBoolean(ntp_prefs::kNtpShortcutsVisible,
                      prefs->GetBoolean(kNewTabPageShowTopSites));
  }

  // The toggle to turn off all widgets used to simply turn off
  // all existing widgets. We later introduced a pref so that future
  // new widgets do not show for that user. Perform a one-off migration
  // for known widgets at the time to set this new pref.
  const PrefService::Preference* hide_widgets_pref =
      prefs->FindPreference(kNewTabPageHideAllWidgets);
  if (!hide_widgets_pref->HasUserSetting()) {
    VLOG(1) << "Migrating hide widget pref...";
    bool all_were_off = true;
    prefs->SetBoolean(kNewTabPageHideAllWidgets, true);
    VLOG(1) << "Done migrating hide widget pref: " << all_were_off;
  }

  // Clear deprecated prefs.
  ClearNewTabPageProfilePrefs(prefs);
}

void RegisterNewTabPagePrefsForMigration(
    user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterBooleanPref(kNewTabPageShowTopSites, true);
}

}  // namespace new_tab_page
