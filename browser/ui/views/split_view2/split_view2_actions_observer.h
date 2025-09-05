/* Copyright (c) 2025 The AI Wize Authors. All rights reserved. */

#ifndef BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_ACTIONS_OBSERVER_H_
#define BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_ACTIONS_OBSERVER_H_

#include "base/observer_list_types.h"

class SplitView2ActionsObserver : public base::CheckedObserver {
 public:
  virtual void OnReloadAction() {}
  virtual void OnHomeAction() {}
};

#endif  // BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_ACTIONS_OBSERVER_H_
