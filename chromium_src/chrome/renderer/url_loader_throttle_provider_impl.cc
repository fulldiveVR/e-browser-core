/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/renderer/url_loader_throttle_provider_impl.h"

#include "brave/components/body_sniffer/body_sniffer_throttle.h"
#include "brave/renderer/brave_content_renderer_client.h"
#include "services/network/public/cpp/resource_request.h"
#include "third_party/blink/public/common/loader/resource_type_util.h"
#include "third_party/blink/public/web/web_local_frame.h"


namespace {

std::unique_ptr<blink::URLLoaderThrottle> MaybeCreateOnionDomainThrottle(
    BraveContentRendererClient* brave_content_renderer_client) {
  return nullptr;
}
}  // namespace

#define IsRequestDestinationFrame                                         \
  IsRequestDestinationFrame(request.destination);                         \
  if (auto onion_domain_throttle = MaybeCreateOnionDomainThrottle(        \
          static_cast<BraveContentRendererClient*>(                       \
              chrome_content_renderer_client_))) {                        \
    throttles.emplace_back(std::move(onion_domain_throttle));             \
  }                                                                       \
  blink::IsRequestDestinationFrame

#include "src/chrome/renderer/url_loader_throttle_provider_impl.cc"

#undef IsRequestDestinationFrame
