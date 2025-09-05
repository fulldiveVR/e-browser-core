// Copyright (c) 2024 The AI Wize Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import { getLocale } from './background/api/localeAPI'

const config = { attributes: true, childList: true, subtree: true }

const callback = () => {
  document.querySelectorAll('div.v-list-item-title,div.v-list-item-subtitle,div.v-card-title,label.v-field-label,span.v-btn__content,span.nav-item-text').forEach(div => {
    var text = div.textContent || '';
    var new_text = '';
    if (text === 'System') {
      new_text = getLocale('dashboardSystem');
    } else if (text === 'Memory') {
      new_text = getLocale('dashboardMemory');
    } else if (text === 'Downloads') {
      new_text = getLocale('dashboardDownloadsTitle');
    } else if (text === 'Settings') {
      new_text = getLocale('dashboardSettingsTitle');
    } else if (text === 'History') {
      new_text = getLocale('dashboardHistoryTitle');
    } else if (text === 'Bookmarks') {
      new_text = getLocale('dashboardBookmarksTitle');
    } else if (text === 'AI Wize LLM') {
      new_text = getLocale('dashboardLLMTitle');
    } else if (text === 'Ready to start') {
      new_text = getLocale('dashboardReadyToStart');
    } else if (text === 'Will be downloaded') {
      new_text = getLocale('dashboardWillBeDownloaded');
    } else if (text === 'Model') {
      new_text = getLocale('dashboardModel');
    } else if (text === ' Save ') {
      new_text = getLocale('dashboardSaveButton');
    } else if (text === ' Reset ') {
      new_text = getLocale('dashboardResetButton');
    } else if (text === ' Start ') {
      new_text = getLocale('dashboardStartButton');
    } else if (text === ' Stop ') {
      new_text = getLocale('dashboardStopButton');
    } else if (text === ' Restart ') {
      new_text = getLocale('dashboardRestartButton');
    } else if (text.includes('Current model')) {
      new_text = text.replace('Current model', getLocale('dashboardCurrentModel'))
    } else if (text.includes('Downloading')) {
      new_text = text.replace('Downloading', getLocale('dashboardDownloading')).replace('parts', getLocale('dashboardParts'))
    }
    if (new_text !== '' && text != new_text) {
      div.textContent = text
    }
  });
}

const observer: MutationObserver = new MutationObserver(callback)
observer.observe(document, config)
