/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_CHROMIUM_SRC_CHROME_COMMON_CHROME_ICON_RESOURCES_WIN_H_
#define BRAVE_CHROMIUM_SRC_CHROME_COMMON_CHROME_ICON_RESOURCES_WIN_H_

namespace icon_resources {

// This file contains the indices of icon resources in brave_exe.rc.

enum {
  // The main application icon is always index 0.
  kApplicationIndex = 0,

#if defined(OFFICIAL_BUILD)
  // Legacy indices that are no longer used.
  kApplication2Index = 1,
  kApplication3Index = 2,
  kApplication4Index = 3,

  // The AI Wize Canary application icon.
  kSxSApplicationIndex = 4,

  // The AI Wize App Launcher icon.
  kAppLauncherIndex = 5,

  // The AI Wize App Launcher Canary icon.
  kSxSAppLauncherIndex = 6,

  // The AI Wize incognito icon.
  kIncognitoIndex = 7,

  // The AI Wize Dev application icon.
  kDevApplicationIndex = 8,

  // The AI Wize Beta application icon.
  kBetaApplicationIndex = 9,

  // The various file type icon(ex, pdf).
  kFileTypeIndex = 10,
  kBetaFileTypeIndex = 11,
  kDevFileTypeIndex = 12,
  kSxSFileTypeIndex = 13,
#else
  // The AI Wize Developer App Launcher icon.
  kAppLauncherIndex = 1,

  // The AI Wize Developer incognito icon.
  kIncognitoIndex = 2,
#endif
};

}  // namespace icon_resources

#endif  // BRAVE_CHROMIUM_SRC_CHROME_COMMON_CHROME_ICON_RESOURCES_WIN_H_
