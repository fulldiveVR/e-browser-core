/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "content/browser/renderer_host/render_frame_host_impl.h"

#define BRAVE_RENDER_FRAME_HOST_IMPL_COMPUTE_ISOLATION_INFO_INTERNAL \
  SetEphemeralStorageNonce(top_frame_origin);

#define BRAVE_RENDER_FRAME_HOST_IMPL_COMPUTE_NONCE                 \
  if (auto ephemeral_storage_nonce = GetEphemeralStorageNonce()) { \
    return ephemeral_storage_nonce;                                \
  }

#include "src/content/browser/renderer_host/render_frame_host_impl.cc"

#undef BRAVE_RENDER_FRAME_HOST_IMPL_COMPUTE_ISOLATION_INFO_INTERNAL
#undef BRAVE_RENDER_FRAME_HOST_IMPL_COMPUTE_NONCE

namespace content {

void RenderFrameHostImpl::GetImageAt(
    int x,
    int y,
    base::OnceCallback<void(const SkBitmap&)> callback) {
  gfx::PointF point_in_view =
      GetView()->TransformRootPointToViewCoordSpace(gfx::PointF(x, y));
  GetAssociatedLocalFrame()->GetImageAt(
      gfx::Point(point_in_view.x(), point_in_view.y()), std::move(callback));
}

void RenderFrameHostImpl::SetEphemeralStorageNonce(
    const url::Origin& top_frame_origin) {
  if (!is_main_frame()) {
    return;
  }

  if (auto ephemeral_storage_nonce =
          GetContentClient()->browser()->GetEphemeralStorageNonce(
              this, top_frame_origin)) {
    ephemeral_storage_nonce_ = std::move(*ephemeral_storage_nonce);
  } else {
    ephemeral_storage_nonce_.emplace();
  }

  DVLOG(2) << __func__ << " " << top_frame_origin << " "
           << (ephemeral_storage_nonce_ ? ephemeral_storage_nonce_->ToString()
                                        : std::string());
}

absl::optional<base::UnguessableToken>
RenderFrameHostImpl::GetEphemeralStorageNonce() const {
  const RenderFrameHostImpl* main_rfh = this;
  while (main_rfh->parent_) {
    main_rfh = main_rfh->parent_;
  }

  CHECK(main_rfh->ephemeral_storage_nonce_);
  if (main_rfh->ephemeral_storage_nonce_->is_empty()) {
    return absl::nullopt;
  }

  return *main_rfh->ephemeral_storage_nonce_;
}

}  // namespace content
