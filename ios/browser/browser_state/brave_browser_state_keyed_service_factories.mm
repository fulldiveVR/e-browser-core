/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/ios/browser/browser_state/brave_browser_state_keyed_service_factories.h"

#include "brave/ios/browser/skus/skus_service_factory.h"
#include "brave/ios/browser/url_sanitizer/url_sanitizer_service_factory+private.h"

namespace brave {

void EnsureBrowserStateKeyedServiceFactoriesBuilt() {
  skus::SkusServiceFactory::GetInstance();
  brave::URLSanitizerServiceFactory::GetInstance();
}

}  // namespace brave
