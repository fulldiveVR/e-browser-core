/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */

#ifndef BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_SEPARATOR_H_
#define BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_SEPARATOR_H_

#include "base/memory/raw_ptr.h"
#include "base/scoped_observation.h"
#include "brave/browser/ui/views/split_view2/split_view2_separator_delegate.h"
#include "ui/views/controls/resize_area.h"
#include "ui/views/controls/resize_area_delegate.h"
#include "ui/views/view.h"
#include "ui/views/widget/widget.h"
#include "ui/views/widget/widget_observer.h"

class Browser;

// A separator view that is located between contents web views in BrowserView.
// This separator is used to resize the contents web views.
class SplitView2Separator : public views::ResizeArea,
                            public views::ResizeAreaDelegate,
                            public views::WidgetObserver,
                            public views::ViewObserver {
  METADATA_HEADER(SplitView2Separator, views::ResizeArea)
 public:
  explicit SplitView2Separator(Browser* browser);
  ~SplitView2Separator() override;

  void set_delegate(SplitView2SeparatorDelegate* delegate) {
    resize_area_delegate_ = delegate;
  }

  // views::View:
  void AddedToWidget() override;
  bool OnMousePressed(const ui::MouseEvent& event) override;
  void ViewHierarchyChanged(
      const views::ViewHierarchyChangedDetails& details) override;
  void OnBoundsChanged(const gfx::Rect& previous_bounds) override;

  // views::ResizeAreaDelegate:
  void OnResize(int resize_amount, bool done_resizing) override;

  // views::WidgetObserver:
  void OnWidgetBoundsChanged(views::Widget* widget,
                             const gfx::Rect& new_bounds) override;

  // views::ViewObserver:
  void OnViewBoundsChanged(views::View* observed_view) override;

 private:
  raw_ptr<Browser> browser_ = nullptr;

  raw_ptr<SplitView2SeparatorDelegate, DanglingUntriaged>
      resize_area_delegate_ = nullptr;

  base::ScopedObservation<views::Widget, views::WidgetObserver>
      parent_widget_observation_{this};

  base::ScopedObservation<views::View, views::ViewObserver>
      parent_view_observation_{this};
};

#endif  // BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_SEPARATOR_H_
