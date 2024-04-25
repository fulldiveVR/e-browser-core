// Copyright (c) 2024 The AI Wize Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import { getLocale } from './background/api/localeAPI'

const config = { attributes: true, childList: true, subtree: true }

const callback = () => {
  console.log("dashboard test mutable")
  document.querySelectorAll('div.v-list-item-title,div.v-list-item-subtitle,div.v-card-title,label.v-field-label,span.v-btn__content').forEach(div => {
    var text = div.textContent || '';
    var changed = false;
    console.log(text)
    if (text === 'System') {
      changed = true;
      text = getLocale('dashboardSystem');
    } else if (text === 'Memory') {
      changed = true;
      text = getLocale('dashboardMemory');
    } else if (text === 'Will be downloaded') {
      changed = true;
      text = getLocale('dashboardWillBeDownloaded');
    } else if (text === 'Model') {
      changed = true;
      text = getLocale('dashboardModel');
    } else if (text === ' Save ') {
      changed = true;
      text = getLocale('dashboardSaveButton');
    } else if (text === ' Reset ') {
      changed = true;
      text = getLocale('dashboardResetButton');
    } else if (text === ' Start ') {
      changed = true;
      text = getLocale('dashboardStartButton');
    } else if (text === ' Stop ') {
      changed = true;
      text = getLocale('dashboardStopButton');
    } else if (text === ' Restart ') {
      changed = true;
      text = getLocale('dashboardRestartButton');
    } else if (text.includes('Current model')) {
      changed = true;
      text = text.replace('Current model', getLocale('dashboardCurrentModel'))
    } else if (text.includes('Downloading')) {
      changed = true;
      text = text.replace('Downloading', getLocale('dashboardDownloading')).replace('parts', getLocale('dashboardParts'))
    }
    if(changed) {
      div.textContent = text
    }
  });
}

const observer: MutationObserver = new MutationObserver(callback)
observer.observe(document, config)
