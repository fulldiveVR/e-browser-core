/* Copyright 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/views/frame/brave_window_frame_graphic.h"

#include "brave/grit/brave_theme_resources.h"
#include "content/public/browser/browser_context.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/gfx/canvas.h"
#include "ui/gfx/geometry/rect.h"

BraveWindowFrameGraphic::BraveWindowFrameGraphic(
    content::BrowserContext* context)
    : is_tor_window_(context->IsTor()) {}

BraveWindowFrameGraphic::~BraveWindowFrameGraphic() = default;

void BraveWindowFrameGraphic::Paint(gfx::Canvas* canvas,
                                    const gfx::Rect& frame_bounds) {

}
