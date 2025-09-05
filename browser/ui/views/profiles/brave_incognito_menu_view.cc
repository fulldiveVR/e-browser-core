/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/views/profiles/brave_incognito_menu_view.h"

#include <memory>
#include <optional>
#include <utility>

#include "base/check.h"
#include "brave/grit/brave_generated_resources.h"
#include "chrome/app/vector_icons/vector_icons.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/browser/profiles/profile_window.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_list.h"
#include "chrome/browser/ui/views/chrome_layout_provider.h"
#include "chrome/grit/generated_resources.h"
#include "components/vector_icons/vector_icons.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/models/image_model.h"


namespace {


int GetProfileMenuTitleId(Profile& profile) {
  return IDS_PRIVATE_PROFILE_NAME;
}

int GetProfileMenuCloseButtonTextId(Profile& profile) {
  return IDS_PROFILES_EXIT_PRIVATE;
}

}  // namespace

void BraveIncognitoMenuView::BuildMenu() {

  AddFeatureButton(
      l10n_util::GetStringUTF16(GetProfileMenuCloseButtonTextId(profile())),
      base::BindRepeating(&BraveIncognitoMenuView::OnExitButtonClicked,
                          base::Unretained(this)),
      vector_icons::kCloseIcon);
}

void BraveIncognitoMenuView::AddedToWidget() {
  IncognitoMenuView::AddedToWidget();

  ChromeLayoutProvider* provider = ChromeLayoutProvider::Get();
  // The icon color is set to match the menu text, which guarantees sufficient
  // contrast and a consistent visual appearance.
  const ui::ColorId icon_color = provider->GetTypographyProvider().GetColorId(
      views::style::CONTEXT_LABEL, views::style::STYLE_PRIMARY);

  IdentitySectionParams params;
  params.title = l10n_util::GetStringUTF16(GetProfileMenuTitleId(profile()));
  params.profile_image_padding = std::nearbyint(kIdentityInfoImageSize * 0.25f);
  params.profile_image =
      ui::ImageModel::FromVectorIcon(kIncognitoProfileIcon, icon_color);
  SetProfileIdentityWithCallToAction(std::move(params));
  AddBottomMargin();
}



std::u16string BraveIncognitoMenuView::GetAccessibleWindowTitle() const {
  return IncognitoMenuView::GetAccessibleWindowTitle();
}

void BraveIncognitoMenuView::OnExitButtonClicked() {
    IncognitoMenuView::OnExitButtonClicked();
}
