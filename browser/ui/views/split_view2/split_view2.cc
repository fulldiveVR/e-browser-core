/* Copyright (c) 2025 AI Wize Authors. All rights reserved. */

#include "brave/browser/ui/views/split_view2/split_view2.h"

#include <utility>

#include "base/types/to_address.h"
#include "brave/browser/ui/brave_browser.h"
#include "brave/browser/ui/color/brave_color_id.h"
#include "brave/browser/ui/tabs/features.h"
#include "brave/browser/ui/views/frame/brave_browser_view.h"
#include "brave/browser/ui/views/frame/brave_contents_layout_manager.h"
#include "brave/browser/ui/views/frame/brave_contents_view_util.h"
#include "brave/browser/ui/views/split_view2/split_view2_actions_observer.h"
#include "brave/browser/ui/views/split_view2/split_view2_layout_manager.h"
#include "brave/browser/ui/views/split_view2/split_view2_separator.h"
#include "brave/components/constants/pref_names.h"
#include "brave/ui/color/nala/nala_color_id.h"
#include "chrome/browser/extensions/extension_view_host.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_window/public/browser_window_features.h"
#include "chrome/browser/ui/exclusive_access/exclusive_access_manager.h"
#include "chrome/browser/ui/exclusive_access/fullscreen_controller.h"
#include "chrome/browser/ui/ui_features.h"
#include "chrome/browser/ui/views/frame/contents_layout_manager.h"
#include "chrome/browser/ui/views/frame/contents_web_view.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/compositor/layer.h"
#include "ui/views/background.h"
#include "ui/views/border.h"
#include "ui/views/controls/webview/webview.h"
#include "ui/views/painter.h"

SplitView2::SplitView2(Browser& browser,
                       views::View* contents_container,
                       ContentsWebView* contents_web_view,
                       PrefService* prefs)
    : browser_(browser),
      contents_container_(contents_container),
      contents_web_view_(contents_web_view),
      prefs_(prefs) {
  // Re-parent the |contents_container| to this view.
  AddChildView(
      contents_container->parent()->RemoveChildViewT(contents_container));

  secondary_web_view_ =
      AddChildView(std::make_unique<views::WebView>(browser_->profile()));
  secondary_web_view_->SetVisible(ShoutShowSplitView2());

  split_view_separator_ = AddChildView(
      std::make_unique<SplitView2Separator>(base::to_address(browser_)));

  SetLayoutManager(std::make_unique<SplitView2LayoutManager>(
      contents_container_, secondary_web_view_, split_view_separator_));

  pref_change_registrar_.Init(prefs_);
  pref_change_registrar_.Add(
      kSplitView2Visible, base::BindRepeating(&SplitView2::OnPreferenceChanged,
                                              base::Unretained(this)));
}

SplitView2::~SplitView2() = default;

void SplitView2::WillChangeActiveWebContents(
    BrowserViewKey,
    content::WebContents* old_contents,
    content::WebContents* new_contents) {
  contents_web_view_->SetFastResize(true);
}

void SplitView2::DidChangeActiveWebContents(
    BrowserViewKey,
    content::WebContents* old_contents,
    content::WebContents* new_contents) {
  // Update secondary webview & UI after changing active WebContents.
  UpdateContentsWebViewVisual();

  // Revert back to default state.
  contents_web_view_->SetFastResize(false);
  InvalidateLayout();
}
bool SplitView2::ShoutShowSplitView2() {
  return prefs_->GetBoolean(kSplitView2Visible) &&
         !browser_->profile()->IsIncognitoProfile();
}

void SplitView2::OnPreferenceChanged(const std::string& pref_name) {
  if (pref_name == kSplitView2Visible) {
    secondary_web_view_->SetVisible(ShoutShowSplitView2());
    return;
  }
}
void SplitView2::GetAccessiblePanes(BrowserViewKey,
                                    std::vector<views::View*>* panes) {
  if (!secondary_web_view_->GetVisible()) {
    return;
  }

  panes->push_back(secondary_web_view_);
}

void SplitView2::Layout(PassKey key) {
  LayoutSuperclass<views::View>(this);

  auto* browser_view = static_cast<BraveBrowserView*>(browser_->window());
  if (!browser_view) {
    // This can happen on start up
    return;
  }

  browser_view->NotifyDialogPositionRequiresUpdate();
}

void SplitView2::AddedToWidget() {
  // Initialize secondary view state.
  UpdateSecondaryContentsWebViewVisibility();
}

void SplitView2::OnReloadAction() {
  secondary_web_view_->LoadInitialURL(
      secondary_web_view_->web_contents()->GetURL());
}

void SplitView2::OnHomeAction() {
  secondary_web_view_->LoadInitialURL(GURL("chrome://ai-combiner-chat/"));
}

void SplitView2::UpdateContentsWebViewVisual() {
  UpdateContentsWebViewBorder();
  UpdateSecondaryContentsWebViewVisibility();
}

void SplitView2::UpdateContentsWebViewBorder() {
  if (browser_->tab_strip_model()->empty()) {
    // Happens on startup
    return;
  }

  if (browser_->IsBrowserClosing()) {
    return;
  }

  auto* cp = GetColorProvider();
  if (!cp) {
    return;
  }

  contents_container_->SetBorder(nullptr);
  BraveContentsLayoutManager::GetLayoutManagerForView(contents_container_)
      ->SetWebContentsBorderInsets({});

  secondary_web_view_->SetBorder(nullptr);
  SchedulePaint();
}

void SplitView2::UpdateSecondaryContentsWebViewVisibility() {
  if (browser_->IsBrowserClosing()) {
    secondary_web_view_->SetWebContents(nullptr);
    return;
  }

  split_view_separator_->SetVisible(secondary_web_view_->GetVisible());

  InvalidateLayout();
}

bool SplitView2::ShouldHideSecondaryContentsByTabFullscreen() const {
  auto* exclusive_access_manager = browser_->GetExclusiveAccessManager();
  if (!exclusive_access_manager) {
    return false;
  }

  return exclusive_access_manager->fullscreen_controller()->IsTabFullscreen();
}

SplitView2LayoutManager* SplitView2::GetSplitView2LayoutManager() {
  return const_cast<SplitView2LayoutManager*>(
      const_cast<const SplitView2*>(this)->GetSplitView2LayoutManager());
}

const SplitView2LayoutManager* SplitView2::GetSplitView2LayoutManager() const {
  return static_cast<SplitView2LayoutManager*>(GetLayoutManager());
}

BEGIN_METADATA(SplitView2)
END_METADATA
