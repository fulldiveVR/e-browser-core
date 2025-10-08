/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

 
 export interface BraveClearBrowsingDataDialogBrowserProxy {
  clearBraveAdsData: () => void
 }

 export class BraveClearBrowsingDataDialogBrowserProxyImpl
    implements BraveClearBrowsingDataDialogBrowserProxy {


  clearBraveAdsData() {
  }

  static getInstance(): BraveClearBrowsingDataDialogBrowserProxyImpl {
    return instance ||
        (instance = new BraveClearBrowsingDataDialogBrowserProxyImpl())
  }
}

let instance: BraveClearBrowsingDataDialogBrowserProxyImpl|null = null
