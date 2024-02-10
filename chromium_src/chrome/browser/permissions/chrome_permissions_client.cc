/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/permissions/chrome_permissions_client.h"

#define MaybeCreateMessageUI MaybeCreateMessageUI_ChromiumImpl
#include "src/chrome/browser/permissions/chrome_permissions_client.cc"
#undef MaybeCreateMessageUI

#include <vector>

#include "build/build_config.h"
#include "components/permissions/permission_request.h"
#include "components/permissions/request_type.h"
#include "url/origin.h"

#if BUILDFLAG(IS_ANDROID)
#include "components/permissions/android/permission_prompt/permission_prompt_android.h"
#endif

bool ChromePermissionsClient::BraveCanBypassEmbeddingOriginCheck(
    const GURL& requesting_origin,
    const GURL& embedding_origin,
    ContentSettingsType type) {

  return CanBypassEmbeddingOriginCheck(requesting_origin, embedding_origin);
}

#if BUILDFLAG(IS_ANDROID)
std::unique_ptr<ChromePermissionsClient::PermissionMessageDelegate>
ChromePermissionsClient::MaybeCreateMessageUI(
    content::WebContents* web_contents,
    ContentSettingsType type,
    base::WeakPtr<permissions::PermissionPromptAndroid> prompt) {

  return MaybeCreateMessageUI_ChromiumImpl(web_contents, type,
                                           std::move(prompt));
}
#endif
