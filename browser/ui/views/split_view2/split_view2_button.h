/* Copyright (c) 2025 The AI Wize Authors. All rights reserved. */

#ifndef BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_BUTTON_H_
#define BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_BUTTON_H_

#include "base/memory/raw_ref.h"
#include "brave/browser/ui/views/split_view2/split_view2_actions_observer.h"
#include "chrome/browser/ui/views/toolbar/toolbar_button.h"
#include "components/prefs/pref_member.h"
#include "ui/base/metadata/metadata_header_macros.h"

class Browser;

class SplitView2Button : public ToolbarButton,
                         public SplitView2ActionsObserver {
  METADATA_HEADER(SplitView2Button, ToolbarButton)

 public:
  explicit SplitView2Button(Browser* browser);
  SplitView2Button(const SplitView2Button&) = delete;
  SplitView2Button& operator=(const SplitView2Button&) = delete;
  ~SplitView2Button() override;

  void UpdateState();
  void AddObserver(SplitView2ActionsObserver* observer);
  void RemoveObserver(SplitView2ActionsObserver* observer);

  void OnReloadAction() override;
  void OnHomeAction() override;

 private:
  void ButtonPressed();

  const raw_ref<Browser> browser_;
  base::ObserverList<SplitView2ActionsObserver> observer_list_;
};

#endif  // BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_BUTTON_H_
