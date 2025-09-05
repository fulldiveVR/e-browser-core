/* Copyright (c) 2025 The AI Wize Authors. All rights reserved. */

#include "brave/browser/ui/views/split_view2/split_view2_layout_manager.h"

#include "base/feature_list.h"
#include "brave/browser/ui/tabs/features.h"
#include "brave/browser/ui/views/split_view2/split_view2_separator.h"
#include "ui/views/view.h"

namespace {

int ClampSplitViewSizeDelta(const views::View* contents_view, int size_delta) {
  constexpr int kMinWidth = 300;
  const auto half_size =
      (contents_view->width() -
       SplitView2LayoutManager::kSpacingBetweenContentsWebViews) /
      2;

  if (half_size < kMinWidth) {
    // in this case |kMinWidth - half_size| > |half_size - kMinWidth| and
    // std::clamp is UB.
    return 0;
  }

  return std::clamp(size_delta, /*min*/ kMinWidth - half_size,
                    /*max*/ half_size - kMinWidth);
}

}  // namespace

SplitView2LayoutManager::SplitView2LayoutManager(
    views::View* contents_container,
    views::View* secondary_contents_container,
    SplitView2Separator* split_view_separator)
    : contents_container_(contents_container),
      secondary_contents_container_(secondary_contents_container),
      split_view_separator_(split_view_separator) {
  split_view_separator_->set_delegate(this);

  base_delta_size = 1000;
  split_view_size_delta_ = base_delta_size;
}

SplitView2LayoutManager::~SplitView2LayoutManager() = default;

void SplitView2LayoutManager::OnDoubleClicked() {
  ongoing_split_view_size_delta_ = 0;
  split_view_size_delta_ = base_delta_size;
  InvalidateHost(true);
}

void SplitView2LayoutManager::OnResize(int resize_amount, bool done_resizing) {
  ongoing_split_view_size_delta_ = resize_amount;
  if (done_resizing) {
    split_view_size_delta_ += ongoing_split_view_size_delta_;
    split_view_size_delta_ =
        ClampSplitViewSizeDelta(host_view(), split_view_size_delta_);
    ongoing_split_view_size_delta_ = 0;
  }

  InvalidateHost(true);
}

views::ProposedLayout SplitView2LayoutManager::CalculateProposedLayout(
    const views::SizeBounds& size_bounds) const {
  views::ProposedLayout layouts;
  if (!size_bounds.is_fully_bounded()) {
    return layouts;
  }

  int height = size_bounds.height().value();
  int width = size_bounds.width().value();

  const gfx::Size container_size(width, height);
  layouts.host_size = container_size;
  gfx::Rect bounds(container_size);

  auto add_to_child_layout = [&layouts, &container_size,
                              host_view = host_view()](
                                 views::View* child, const gfx::Rect& bounds) {
    layouts.child_layouts.emplace_back(child, child->GetVisible(),
                                       host_view->GetMirroredRect(bounds),
                                       views::SizeBounds(container_size));
  };

  if (!secondary_contents_container_->GetVisible()) {
    add_to_child_layout(contents_container_.get(), bounds);
    return layouts;
  }

  const auto size_delta = ClampSplitViewSizeDelta(
      host_view(), split_view_size_delta_ + ongoing_split_view_size_delta_);
  bounds.set_width((bounds.width()) / 2 - 1 + size_delta);
  if (show_main_web_contents_at_tail_) {
    add_to_child_layout(secondary_contents_container_.get(), bounds);
  } else {
    add_to_child_layout(contents_container_.get(), bounds);
  }

  int space_x = bounds.right();
  bounds.set_x(bounds.right() + 2);
  bounds.set_width(host_view()->width() - bounds.x());
  if (show_main_web_contents_at_tail_) {
    add_to_child_layout(contents_container_.get(), bounds);
  } else {
    add_to_child_layout(secondary_contents_container_.get(), bounds);
  }

  bounds.set_x(space_x - 3);
  bounds.set_width(10);
  add_to_child_layout(split_view_separator_.get(), bounds);

  return layouts;
}
