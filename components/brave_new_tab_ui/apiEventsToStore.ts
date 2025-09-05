// Copyright (c) 2019 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import getActions from './api/getActions'
import * as preferencesAPI from './api/preferences'
import * as statsAPI from './api/stats'
import * as topSitesAPI from './api/topSites'
import getNTPBrowserAPI, { Background, CustomBackground } from './api/background'
import { getInitialData } from './api/initialData'
import * as backgroundData from './data/backgrounds'

async function updatePreferences (prefData: NewTab.Preferences) {
  getActions().preferencesUpdated(prefData)
}

async function updateStats (statsData: statsAPI.Stats) {
  getActions().statsUpdated(statsData)
}



async function onMostVisitedInfoChanged (topSites: topSitesAPI.MostVisitedInfoChanged) {
  getActions().tilesUpdated(topSites.tiles)
  getActions().topSitesStateUpdated(topSites.visible, topSites.custom_links_enabled, topSites.custom_links_num)
}

async function onBackgroundUpdated (background: Background) {
  getActions().customBackgroundUpdated(background)
}

async function onCustomImageBackgroundsUpdated (backgrounds: CustomBackground[]) {
  getActions().customImageBackgroundsUpdated(backgrounds)
}

// Not marked as async so we don't return a promise
// and confuse callers
export function wireApiEventsToStore () {
  // Get initial data and dispatch to store
  getInitialData()
  .then((initialData) => {
    getActions().setInitialData(initialData)
    // Listen for API changes and dispatch to store
    topSitesAPI.addMostVistedInfoChangedListener(onMostVisitedInfoChanged)
    topSitesAPI.updateMostVisitedInfo()
    statsAPI.addChangeListener(updateStats)
    preferencesAPI.addChangeListener(updatePreferences)
    backgroundData.updateImages(initialData.braveBackgrounds)

    getNTPBrowserAPI().addBackgroundUpdatedListener(onBackgroundUpdated)
    getNTPBrowserAPI().addCustomImageBackgroundsUpdatedListener(onCustomImageBackgroundsUpdated)
    getNTPBrowserAPI().addSearchPromotionDisabledListener(() => getActions().searchPromotionDisabled())
  })
  .catch(e => {
    console.error('New Tab Page fatal error:', e)
  })
}










