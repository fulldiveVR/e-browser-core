/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */

#ifndef BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_H_
#define BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_H_

#include <memory>
#include <vector>

#include "base/memory/raw_ptr.h"
#include "base/memory/raw_ref.h"
#include "base/scoped_observation.h"
#include "base/types/pass_key.h"
#include "brave/browser/ui/views/split_view2/split_view2_actions_observer.h"
#include "brave/browser/ui/views/split_view2/split_view2_layout_manager.h"
#include "chrome/browser/ui/exclusive_access/fullscreen_observer.h"
#include "chrome/browser/ui/views/frame/scrim_view.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/prefs/pref_service.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/gfx/geometry/rounded_corners_f.h"
#include "ui/views/view.h"
#include "ui/views/widget/widget_observer.h"

namespace content {
class WebContents;
}  // namespace content

namespace views {
class WebView;
}  // namespace views

class BraveBrowserView;
class Browser;
class ContentsWebView;
class SplitView2LayoutManager;
class SplitView2Separator;

// Contains a pair of contents container view.
class SplitView2 : public views::View, public SplitView2ActionsObserver {
  METADATA_HEADER(SplitView2, views::View)
 public:
  using BrowserViewKey = base::PassKey<BraveBrowserView>;

  static constexpr int kBorderThickness = 2;

  SplitView2(Browser& browser,
             views::View* contents_container,
             ContentsWebView* contents_web_view,
             PrefService* prefs);

  ~SplitView2() override;

  // Called before/after BrowserView::OnActiveTabChanged() as we have some
  // jobs such as reducing flickering while active tab changing. See the
  // comments of each methods for more details.
  void WillChangeActiveWebContents(BrowserViewKey,
                                   content::WebContents* old_contents,
                                   content::WebContents* new_contents);
  void DidChangeActiveWebContents(BrowserViewKey,
                                  content::WebContents* old_contents,
                                  content::WebContents* new_contents);
  void OnPreferenceChanged(const std::string& pref_name);
  // Fills secondary web views if accessible.
  void GetAccessiblePanes(BrowserViewKey, std::vector<views::View*>* panes);

  views::WebView* secondary_web_view() { return secondary_web_view_; }

  // views::View:
  void Layout(PassKey) override;
  void AddedToWidget() override;

  void OnReloadAction() override;
  void OnHomeAction() override;

 private:
  void UpdateContentsWebViewVisual();
  void UpdateContentsWebViewBorder();
  void UpdateSecondaryContentsWebViewVisibility();
  bool ShoutShowSplitView2();

  SplitView2LayoutManager* GetSplitView2LayoutManager();
  const SplitView2LayoutManager* GetSplitView2LayoutManager() const;
  bool ShouldHideSecondaryContentsByTabFullscreen() const;

  raw_ref<Browser> browser_;

  raw_ptr<views::View> contents_container_ = nullptr;
  raw_ptr<views::WebView> contents_web_view_ = nullptr;

  raw_ptr<views::WebView> secondary_web_view_ = nullptr;
  raw_ptr<SplitView2Separator> split_view_separator_ = nullptr;

  PrefChangeRegistrar pref_change_registrar_;
  raw_ptr<PrefService> prefs_ = nullptr;
};

#endif  // BRAVE_BROWSER_UI_VIEWS_SPLIT_VIEW2_SPLIT_VIEW2_H_
