/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */


#ifndef BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_SEPARATOR_DELEGATE_H_
#define BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_SEPARATOR_DELEGATE_H_

#include "ui/views/controls/resize_area_delegate.h"

class SplitView2SeparatorDelegate : public views::ResizeAreaDelegate {
 public:
  virtual void OnDoubleClicked() = 0;
};

#endif  // BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_SEPARATOR_DELEGATE_H_
