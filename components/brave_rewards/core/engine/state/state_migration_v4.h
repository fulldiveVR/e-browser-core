/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_ENGINE_STATE_STATE_MIGRATION_V4_H_
#define BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_ENGINE_STATE_STATE_MIGRATION_V4_H_

#include "base/memory/raw_ref.h"
#include "brave/components/brave_rewards/core/engine/rewards_callbacks.h"

namespace brave_rewards::internal {
class RewardsEngine;

namespace state {

class StateMigrationV4 {
 public:
  explicit StateMigrationV4(RewardsEngine& engine);
  ~StateMigrationV4();

  void Migrate(ResultCallback callback);

 private:
  const raw_ref<RewardsEngine> engine_;
};

}  // namespace state
}  // namespace brave_rewards::internal

#endif  // BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_ENGINE_STATE_STATE_MIGRATION_V4_H_
