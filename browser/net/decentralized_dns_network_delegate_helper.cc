/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/net/decentralized_dns_network_delegate_helper.h"

#include <optional>
#include <utility>
#include <vector>

#include "brave/components/decentralized_dns/core/constants.h"
#include "brave/components/decentralized_dns/core/utils.h"
#include "brave/components/ipfs/ipfs_utils.h"
#include "chrome/browser/browser_process.h"
#include "content/public/browser/browser_context.h"
#include "net/base/net_errors.h"

namespace decentralized_dns {

int OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(
    const brave::ResponseCallback& next_callback,
    std::shared_ptr<brave::BraveRequestInfo> ctx) {
  DCHECK(!next_callback.is_null());

  if (!ctx->browser_context || ctx->browser_context->IsOffTheRecord() ||
      !g_browser_process) {
    return net::OK;
  }

  return net::OK;
}

void OnBeforeURLRequest_UnstoppableDomainsRedirectWork(
    const brave::ResponseCallback& next_callback,
    std::shared_ptr<brave::BraveRequestInfo> ctx,
    const std::optional<GURL>& url,
    const std::string& error_message) {

  if (!next_callback.is_null()) {
    next_callback.Run();
  }
}

}  // namespace decentralized_dns
