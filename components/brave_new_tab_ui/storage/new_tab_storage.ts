// Copyright (c) 2020 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// Utils
import { debounce } from '../../common/debounce'
import { loadTimeData } from '../../common/loadTimeData'

export const keyName = 'new-tab-data'

export const defaultState: NewTab.State = {
  initialDataLoaded: false,
  textDirection: loadTimeData.getString('textdirection'),
  featureFlagBraveNewsPromptEnabled: loadTimeData.getBoolean('featureFlagBraveNewsPromptEnabled'),
  featureFlagBraveNewsFeedV2Enabled: loadTimeData.getBoolean('featureFlagBraveNewsFeedV2Enabled'),
  featureCustomBackgroundEnabled: loadTimeData.getBoolean('featureCustomBackgroundEnabled'),
  searchPromotionEnabled: false,
  showBackgroundImage: false,
  showStats: false,
  showToday: false,
  showClock: false,
  clockFormat: '',
  showTopSites: false,
  customLinksEnabled: false,
  customLinksNum: 0,
  showBitcoinDotCom: false,
  hideAllWidgets: false,
  brandedWallpaperOptIn: false,
  isBrandedWallpaperNotificationDismissed: true,
  isBraveNewsOptedIn: false,
  showEmptyPage: false,
  bitcoinDotComSupported: false,
  isIncognito: chrome.extension.inIncognitoContext,
  useAlternativePrivateSearchEngine: false,
  showAlternativePrivateSearchEngineToggle: false,
  torCircuitEstablished: false,
  torInitProgress: '',
  isTor: false,
  isQwant: false,
  stats: {
    adsBlockedStat: 0,
    javascriptBlockedStat: 0,
    bandwidthSavedStat: 0,
    httpsUpgradesStat: 0,
    fingerprintingBlockedStat: 0
  },

  currentStackWidget: '',
  removedStackWidgets: [],
  // Order is ascending, with last entry being in the foreground
  widgetStackOrder: [],
  customImageBackgrounds: []
}

if (chrome.extension.inIncognitoContext) {
  defaultState.isTor = loadTimeData.getBoolean('isTor')
  defaultState.isQwant = loadTimeData.getBoolean('isQwant')
}

// Ensure any new stack widgets introduced are put behind
// the others, and not re-added unecessarily if removed
// at one point.
export const addNewStackWidget = (state: NewTab.State) => {
  defaultState.widgetStackOrder.map((widget: NewTab.StackWidget) => {
    if (!state.widgetStackOrder.includes(widget) &&
        !state.removedStackWidgets.includes(widget)) {
      state.widgetStackOrder.unshift(widget)
    }
  })
  return state
}

const cleanData = (state: NewTab.State) => {
  return state
}

export const load = (): NewTab.State => {
  const data: string | null = window.localStorage.getItem(keyName)
  let state = defaultState
  let storedState

  if (data) {
    try {
      storedState = JSON.parse(data)
      // add defaults for non-peristant data
      state = {
        ...state,
        ...storedState
      }
    } catch (e) {
      console.error('[NewTabData] Could not parse local storage data: ', e)
    }
  }
  return cleanData(state)
}

export const debouncedSave = debounce<NewTab.State>((data: NewTab.State) => {
  if (data) {
    // TODO(petemill): This should be of type NewTab.PersistantState, and first
    // fix errors related to properties which shouldn't be defined as persistant
    // (or are obsolete).
    const dataToSave = {
      bitcoinDotComSupported: data.bitcoinDotComSupported,
      removedStackWidgets: data.removedStackWidgets,
      widgetStackOrder: data.widgetStackOrder
    }
    window.localStorage.setItem(keyName, JSON.stringify(dataToSave))
  }
}, 50)
