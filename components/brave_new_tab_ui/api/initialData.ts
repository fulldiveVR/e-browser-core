// Copyright (c) 2019 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as preferencesAPI from './preferences'
import * as statsAPI from './stats'
import * as privateTabDataAPI from './privateTabData'
import * as wallpaper from './wallpaper'
import getNTPBrowserAPI from './background'

export type InitialData = {
  preferences: NewTab.Preferences
  stats: statsAPI.Stats
  privateTabData: privateTabDataAPI.PrivateTabData
  wallpaperData?: NewTab.Wallpaper
  braveBackgrounds: NewTab.BraveBackground[]
  customImageBackgrounds: NewTab.ImageBackground[]
  searchPromotionEnabled: boolean
}

const isIncognito: boolean = chrome.extension.inIncognitoContext

// Gets all data required for the first render of the page
export async function getInitialData (): Promise<InitialData> {
  try {
    console.timeStamp('Getting initial data...')
    const [
      preferences,
      stats,
      privateTabData,
      wallpaperData,
      braveBackgrounds,
      customImageBackgrounds,
      searchPromotionEnabled
    ] = await Promise.all([
      preferencesAPI.getPreferences(),
      statsAPI.getStats(),
      privateTabDataAPI.getPrivateTabData(),
      !isIncognito ? wallpaper.getWallpaper() : Promise.resolve(undefined),
      new Promise((resolve) => {
          resolve(false)
      }),
      new Promise((resolve) => {
        if (!('braveTalk' in chrome)) {
          resolve(false)
          return
        }

        chrome.braveTalk.isSupported((supported: boolean) => {
          resolve(supported)
        })
      }),
      getNTPBrowserAPI().pageHandler.isSearchPromotionEnabled().then(({ enabled }) => enabled),
      getNTPBrowserAPI().pageHandler.getBraveBackgrounds().then(({ backgrounds }) => {
        return backgrounds.map(background => ({ type: 'brave', wallpaperImageUrl: background.imageUrl.url, author: background.author, link: background.link.url }))
      }),
      getNTPBrowserAPI().pageHandler.getCustomImageBackgrounds().then(({ backgrounds }) => {
        return backgrounds.map(background => ({ type: 'image', wallpaperImageUrl: background.url.url }))
      })
    ])
    console.timeStamp('Got all initial data.')
    return {
      preferences,
      stats,
      privateTabData,
      wallpaperData,
      braveBackgrounds,
      customImageBackgrounds,
      searchPromotionEnabled
    } as InitialData
  } catch (e) {
    console.error(e)
    throw Error('Error getting initial data')
  }
}

