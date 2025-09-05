/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/profiles/brave_renderer_updater_factory.h"

#include "base/no_destructor.h"
#include "brave/browser/profiles/brave_renderer_updater.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"

BraveRendererUpdaterFactory::BraveRendererUpdaterFactory()
    : ProfileKeyedServiceFactory(
          "BraveRendererUpdater",
          ProfileSelections::Builder()
              .WithRegular(ProfileSelection::kOwnInstance)
              .WithGuest(ProfileSelection::kOwnInstance)
              .Build()) {
}

BraveRendererUpdaterFactory::~BraveRendererUpdaterFactory() = default;

// static
BraveRendererUpdaterFactory* BraveRendererUpdaterFactory::GetInstance() {
  static base::NoDestructor<BraveRendererUpdaterFactory> instance;
  return instance.get();
}

// static
BraveRendererUpdater* BraveRendererUpdaterFactory::GetForProfile(
    Profile* profile) {
  return static_cast<BraveRendererUpdater*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

std::unique_ptr<KeyedService>
BraveRendererUpdaterFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {

  return std::make_unique<BraveRendererUpdater>(
      static_cast<Profile*>(context),      g_browser_process->local_state());
}

bool BraveRendererUpdaterFactory::ServiceIsCreatedWithBrowserContext() const {
  return true;
}
