/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "brave/components/l10n/common/localization_util.h"
#include "chrome/browser/chooser_controller/title_util.h"
#include "chrome/grit/generated_resources.h"
#include "components/grit/brave_components_strings.h"
#include "content/public/browser/web_contents.h"
#include "ui/base/l10n/l10n_util.h"
#include "url/gurl.h"


#define CreateChooserTitle CreateChooserTitle
#include "src/chrome/browser/ui/hid/hid_chooser_controller.cc"
#undef CreateChooserTitle
