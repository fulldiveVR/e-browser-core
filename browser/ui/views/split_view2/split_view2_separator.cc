/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */

#include "brave/browser/ui/views/split_view2/split_view2_separator.h"

#include <memory>
#include <utility>

#include "base/functional/bind.h"
#include "base/time/time.h"
#include "brave/browser/ui/color/brave_color_id.h"
#include "brave/components/vector_icons/vector_icons.h"
#include "brave/grit/brave_generated_resources.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/color/chrome_color_id.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/base/models/image_model.h"
#include "ui/gfx/animation/slide_animation.h"
#include "ui/gfx/animation/tween.h"
#include "ui/gfx/canvas.h"
#include "ui/gfx/geometry/transform.h"
#include "ui/gfx/scoped_canvas.h"
#include "ui/gfx/text_constants.h"
#include "ui/views/background.h"
#include "ui/views/border.h"
#include "ui/views/controls/button/image_button.h"
#include "ui/views/controls/highlight_path_generator.h"
#include "ui/views/controls/resize_area.h"
#include "ui/views/layout/fill_layout.h"
#include "ui/views/widget/widget.h"
#include "ui/views/widget/widget_delegate.h"

SplitView2Separator::SplitView2Separator(Browser* browser)
    : ResizeArea(this), browser_(browser) {}

SplitView2Separator::~SplitView2Separator() = default;

void SplitView2Separator::AddedToWidget() {
  ResizeArea::AddedToWidget();
}

bool SplitView2Separator::OnMousePressed(const ui::MouseEvent& event) {
  if (event.IsOnlyLeftMouseButton() && event.GetClickCount() == 2) {
    if (resize_area_delegate_) {
      resize_area_delegate_->OnDoubleClicked();
    }
    return true;
  }

  return ResizeArea::OnMousePressed(event);
}

void SplitView2Separator::ViewHierarchyChanged(
    const views::ViewHierarchyChangedDetails& details) {
  ResizeArea::ViewHierarchyChanged(details);

  if (details.is_add && details.child == this) {
    CHECK(!parent_view_observation_.IsObserving())
        << "This is supposed to be called only once.";
    parent_view_observation_.Observe(parent());
  }
}

void SplitView2Separator::OnBoundsChanged(const gfx::Rect& previous_bounds) {
  ResizeArea::OnBoundsChanged(previous_bounds);
}

void SplitView2Separator::OnResize(int resize_amount, bool done_resizing) {
  // When mouse goes toward web contents area, the cursor could have been
  // changed to the normal cursor. Reset it resize cursor.
  GetWidget()->SetCursor(ui::Cursor(ui::mojom::CursorType::kEastWestResize));
  if (resize_area_delegate_) {
    resize_area_delegate_->OnResize(resize_amount, done_resizing);
  }
}

void SplitView2Separator::OnWidgetBoundsChanged(views::Widget* widget,
                                                const gfx::Rect& new_bounds) {}

void SplitView2Separator::OnViewBoundsChanged(views::View* observed_view) {}

BEGIN_METADATA(SplitView2Separator)
END_METADATA
