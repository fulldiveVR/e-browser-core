/* Copyright (c) 2025 The AI Wize Authors. All rights reserved. */

#include "brave/browser/ui/views/split_view2/split_view2_button.h"

#include <memory>

#include "brave/app/vector_icons/vector_icons.h"
#include "brave/browser/ui/views/split_view2/split_view2_actions_observer.h"
#include "brave/components/constants/pref_names.h"
#include "brave/grit/brave_generated_resources.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_window/public/browser_window_features.h"
#include "chrome/browser/ui/views/side_panel/side_panel_ui.h"
#include "chrome/common/pref_names.h"
#include "components/prefs/pref_service.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/menus/simple_menu_model.h"
#include "ui/views/accessibility/view_accessibility.h"
#include "ui/views/context_menu_controller.h"
#include "ui/views/controls/button/button_controller.h"

namespace {

class SidePanelMenuModel : public ui::SimpleMenuModel,
                           public ui::SimpleMenuModel::Delegate {
 private:
  raw_ref<SplitView2ActionsObserver> actions_observer_;

 public:
  explicit SidePanelMenuModel(SplitView2ActionsObserver* actions_observer)
      : ui::SimpleMenuModel(this), actions_observer_(*actions_observer) {
    Build();
  }

  SidePanelMenuModel(const SidePanelMenuModel&) = delete;
  SidePanelMenuModel& operator=(const SidePanelMenuModel&) = delete;
  ~SidePanelMenuModel() override = default;

 private:
  enum ContextMenuCommand { kReloadSplitView2Button, kHomeSplitView2Button };

  void Build() {
    AddItemWithStringId(ContextMenuCommand::kHomeSplitView2Button,
                        IDS_SPLIT_VIEW2_HOME_BUTTON);
    AddItemWithStringId(ContextMenuCommand::kReloadSplitView2Button,
                        IDS_SPLIT_VIEW2_RELOAD_BUTTON);
  }

  // ui::SimpleMenuModel::Delegate:
  void ExecuteCommand(int command_id, int event_flags) override {
    if (command_id == ContextMenuCommand::kReloadSplitView2Button) {
      actions_observer_->OnReloadAction();
    } else if (command_id == ContextMenuCommand::kHomeSplitView2Button) {
      actions_observer_->OnHomeAction();
    }
  }
};

}  // namespace

SplitView2Button::SplitView2Button(Browser* browser)
    : ToolbarButton(base::BindRepeating(&SplitView2Button::ButtonPressed,
                                        base::Unretained(this))),
      browser_(*browser) {
  SetMenuModel(std::make_unique<SidePanelMenuModel>(this));

  SetVectorIcon(kSidebarToolbarButtonRightIcon);  // kSidebarToolbarButtonIcon
  set_context_menu_controller(this);
  button_controller()->set_notify_action(
      views::ButtonController::NotifyAction::kOnPress);
  GetViewAccessibility().SetHasPopup(ax::mojom::HasPopup::kMenu);
}

SplitView2Button::~SplitView2Button() = default;

void SplitView2Button::AddObserver(SplitView2ActionsObserver* observer) {
  observer_list_.AddObserver(observer);
}
void SplitView2Button::RemoveObserver(SplitView2ActionsObserver* observer) {
  observer_list_.RemoveObserver(observer);
}

void SplitView2Button::OnReloadAction() {
  for (auto& observer : observer_list_) {
    observer.OnReloadAction();
  }
}

void SplitView2Button::OnHomeAction() {
  for (auto& observer : observer_list_) {
    observer.OnHomeAction();
  }
}

void SplitView2Button::UpdateState() {
  auto* prefs = browser_->profile()->GetPrefs();
  bool split_view2_visible = prefs->GetBoolean(kSplitView2Visible);
  SetHighlighted(split_view2_visible);
  SetTooltipText(l10n_util::GetStringUTF16(split_view2_visible
                                               ? IDS_TOOLTIP_SPLIT_VIEW2_HIDE
                                               : IDS_TOOLTIP_SPLIT_VIEW2_SHOW));
}

void SplitView2Button::ButtonPressed() {
  auto* prefs = browser_->profile()->GetPrefs();
  prefs->SetBoolean(kSplitView2Visible, !prefs->GetBoolean(kSplitView2Visible));
  UpdateState();
}

BEGIN_METADATA(SplitView2Button)
END_METADATA
