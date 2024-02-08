// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/webui/skus_internals_ui.h"

#include <memory>
#include <string_view>
#include <utility>

#include "base/files/file_util.h"
#include "base/functional/bind.h"
#include "base/json/json_reader.h"
#include "base/json/json_writer.h"
#include "base/notreached.h"
#include "base/strings/utf_string_conversions.h"
#include "base/task/thread_pool.h"
#include "brave/browser/brave_browser_process.h"
#include "brave/browser/ui/webui/brave_webui_source.h"
#include "brave/components/skus/browser/pref_names.h"
#include "brave/components/skus/browser/resources/grit/skus_internals_generated_map.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/chrome_select_file_policy.h"
#include "components/grit/brave_components_resources.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_ui.h"
#include "ui/base/clipboard/scoped_clipboard_writer.h"

namespace {

void SaveSkusStateToFile(const base::FilePath& path,
                         std::string_view skus_state) {
  base::WriteFile(path, skus_state);
}

}  // namespace

SkusInternalsUI::SkusInternalsUI(content::WebUI* web_ui,
                                 const std::string& name)
    : content::WebUIController(web_ui),
      local_state_(g_browser_process->local_state()) {
  CreateAndAddWebUIDataSource(web_ui, name, kSkusInternalsGenerated,
                              kSkusInternalsGeneratedSize,
                              IDR_SKUS_INTERNALS_HTML);
}

SkusInternalsUI::~SkusInternalsUI() = default;

void SkusInternalsUI::BindInterface(
    mojo::PendingReceiver<skus::mojom::SkusInternals> pending_receiver) {
  if (skus_internals_receiver_.is_bound()) {
    skus_internals_receiver_.reset();
  }

  skus_internals_receiver_.Bind(std::move(pending_receiver));
}

void SkusInternalsUI::GetEventLog(GetEventLogCallback callback) {
  // TODO(simonhong): Ask log to SkusService
  NOTIMPLEMENTED_LOG_ONCE();
}

void SkusInternalsUI::GetSkusState(GetSkusStateCallback callback) {
  std::move(callback).Run(GetSkusStateAsString());
}

void SkusInternalsUI::GetVpnState(GetVpnStateCallback callback) {
  base::Value::Dict dict;
  std::string result;
  base::JSONWriter::Write(dict, &result);
  std::move(callback).Run(result);
}

base::Value::Dict SkusInternalsUI::GetVPNOrderInfo() const {
  base::Value::Dict dict;
  return dict;
}

void SkusInternalsUI::ResetSkusState() {
  local_state_->ClearPref(skus::prefs::kSkusState);
}

void SkusInternalsUI::CopySkusStateToClipboard() {
  ui::ScopedClipboardWriter(ui::ClipboardBuffer::kCopyPaste)
      .WriteText(base::UTF8ToUTF16(GetSkusStateAsString()));
}

void SkusInternalsUI::DownloadSkusState() {
  if (select_file_dialog_) {
    return;
  }

  auto* web_contents = web_ui()->GetWebContents();
  select_file_dialog_ = ui::SelectFileDialog::Create(
      this, std::make_unique<ChromeSelectFilePolicy>(web_contents));
  if (!select_file_dialog_) {
    return;
  }

  Profile* profile =
      Profile::FromBrowserContext(web_contents->GetBrowserContext());
  ui::SelectFileDialog::FileTypeInfo file_types;
  file_types.allowed_paths = ui::SelectFileDialog::FileTypeInfo::NATIVE_PATH;
  select_file_dialog_->SelectFile(
      ui::SelectFileDialog::SELECT_SAVEAS_FILE, std::u16string(),
      profile->last_selected_directory().AppendASCII("skus_state.json"),
      &file_types, 0, base::FilePath::StringType(),
      web_contents->GetTopLevelNativeWindow(), nullptr);
}

void SkusInternalsUI::FileSelected(const base::FilePath& path,
                                   int index,
                                   void* params) {
  auto* web_contents = web_ui()->GetWebContents();
  Profile* profile =
      Profile::FromBrowserContext(web_contents->GetBrowserContext());
  profile->set_last_selected_directory(path.DirName());
  select_file_dialog_ = nullptr;

  base::ThreadPool::PostTask(
      FROM_HERE, {base::MayBlock()},
      base::BindOnce(&SaveSkusStateToFile, path, GetSkusStateAsString()));
}

void SkusInternalsUI::FileSelectionCanceled(void* params) {
  select_file_dialog_ = nullptr;
}

std::string SkusInternalsUI::GetLastVPNConnectionError() const {
  std::string error;
  return error;
}

std::string SkusInternalsUI::GetSkusStateAsString() const {
  const auto& skus_state = local_state_->GetDict(skus::prefs::kSkusState);
  base::Value::Dict dict;

  for (const auto kv : skus_state) {
    // Only shows "skus:xx" kv in webui.
    if (!base::StartsWith(kv.first, "skus:")) {
      continue;
    }

    if (auto value = base::JSONReader::Read(kv.second.GetString()); value) {
      dict.Set(kv.first, std::move(*value));
    }
  }

  std::string result;
  base::JSONWriter::Write(dict, &result);
  return result;
}

WEB_UI_CONTROLLER_TYPE_IMPL(SkusInternalsUI)
