/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/browser_commands.h"

#include "base/check.h"
#include "brave/components/commander/common/buildflags/buildflags.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser_commands.h"
#include "chrome/common/webui_url_constants.h"

#define GetReadingListModel GetReadingListModel_ChromiumImpl
#define kChromeUISplitViewNewTabPageURL kChromeUINewTabURL
#include "src/chrome/browser/ui/browser_commands.cc"
#undef kChromeUISplitViewNewTabPageURL
#undef GetReadingListModel

namespace chrome {


ReadingListModel* GetReadingListModel(Browser* browser) {
  return nullptr;
}

}  // namespace chrome
