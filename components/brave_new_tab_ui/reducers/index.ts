// Copyright (c) 2020 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { combineReducers } from 'redux'
import * as storage from '../storage/new_tab_storage'

// Reducers
import newTabStateReducer from './new_tab_reducer'
import gridSitesReducer from './grid_sites_reducer'

export type ApplicationState = NewTab.ApplicationState

export const newTabReducers = (state: NewTab.State | undefined, action: any) => {
  if (state === undefined) {
    state = storage.load()
  }

  const startingState = state
  state = newTabStateReducer(state, action)

  if (state && state !== startingState) {
    storage.debouncedSave(state)
  }

  return state
}

export const mainNewTabReducer = combineReducers<ApplicationState>({
  newTabData: newTabReducers,
  gridSitesData: gridSitesReducer
})

export const newTabReducer = newTabStateReducer
