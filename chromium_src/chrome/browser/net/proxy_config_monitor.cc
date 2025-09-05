/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>

#include "base/check.h"
#include "chrome/browser/profiles/profile.h"


namespace {


}  // namespace

#define BRAVE_PROXY_CONFIG_MONITOR

#include "src/chrome/browser/net/proxy_config_monitor.cc"
#undef BRAVE_PROXY_CONFIG_MONITOR
