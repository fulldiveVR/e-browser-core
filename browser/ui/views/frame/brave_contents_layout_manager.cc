/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/views/frame/brave_contents_layout_manager.h"

#include "base/check.h"
#include "ui/views/view.h"

// static
BraveContentsLayoutManager* BraveContentsLayoutManager::GetLayoutManagerForView(
    views::View* host) {
  return static_cast<BraveContentsLayoutManager*>(host->GetLayoutManager());
}

BraveContentsLayoutManager::BraveContentsLayoutManager(
    views::View* contents_view,
    views::View* lens_overlay_view,
    views::View* reader_mode_toolbar,
    views::View* scrim_view)
    : ContentsLayoutManager(contents_view, lens_overlay_view),
      contents_view_(contents_view),
      reader_mode_toolbar_(reader_mode_toolbar),
      scrim_view_(scrim_view) {
}

BraveContentsLayoutManager::~BraveContentsLayoutManager() = default;

void BraveContentsLayoutManager::SetWebContentsBorderInsets(
    const gfx::Insets& insets) {
  border_insets_ = insets;
  InvalidateHost(true);
}

views::ProposedLayout BraveContentsLayoutManager::CalculateProposedLayout(
    const views::SizeBounds& size_bounds) const {
  views::ProposedLayout layouts =
      ContentsLayoutManager::CalculateProposedLayout(size_bounds);
  return layouts;
}
