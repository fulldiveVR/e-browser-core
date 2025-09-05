/* Copyright (c) 2025 The AI Wize Authors. All rights reserved. */

#ifndef BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_LAYOUT_MANAGER_H_
#define BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_LAYOUT_MANAGER_H_

#include "brave/browser/ui/views/split_view2/split_view2_separator_delegate.h"
#include "ui/views/layout/layout_manager_base.h"
#include "ui/views/layout/proposed_layout.h"

class SplitView2Separator;

class SplitView2LayoutManager : public views::LayoutManagerBase,
                               public SplitView2SeparatorDelegate {
 public:
  // Spacing between |contents_web_view_| and |secondary_contents_web_view_|.
  static constexpr auto kSpacingBetweenContentsWebViews = 3;

  SplitView2LayoutManager(views::View* contents_container,
                         views::View* secondary_contents_container,
                         SplitView2Separator* split_view_separator);
  ~SplitView2LayoutManager() override;

  int split_view_size_delta() const { return split_view_size_delta_; }
  void set_split_view_size_delta(int delta) { split_view_size_delta_ = delta; }

  // When tile's second tab is the active web contents, we need to show the
  // tab after the first tab.
  void show_main_web_contents_at_tail(bool tail) {
    show_main_web_contents_at_tail_ = tail;
  }

  // SplitView2SeparatorDelegate:
  void OnDoubleClicked() override;
  void OnResize(int resize_amount, bool done_resizing) override;

 protected:
  // views::LayoutManagerBase overrides:
  views::ProposedLayout CalculateProposedLayout(
      const views::SizeBounds& size_bounds) const override;

 private:
  raw_ptr<views::View> contents_container_ = nullptr;
  raw_ptr<views::View> secondary_contents_container_ = nullptr;
  raw_ptr<SplitView2Separator> split_view_separator_ = nullptr;

  int base_delta_size = 0;
  int split_view_size_delta_ = 0;
  int ongoing_split_view_size_delta_ = 0;

  bool show_main_web_contents_at_tail_ = false;
};

#endif  // BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_LAYOUT_MANAGER_H_
