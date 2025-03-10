/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/user_attention/user_activity/user_activity_scoring.h"

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "base/strings/string_number_conversions.h"
#include "base/strings/string_util.h"

namespace brave_ads {

namespace {

UserActivityTriggerList SortTriggers(const UserActivityTriggerList& triggers) {
  UserActivityTriggerList sorted_triggers = triggers;

  std::ranges::sort(sorted_triggers, [](const UserActivityTriggerInfo& lhs,
                                        const UserActivityTriggerInfo& rhs) {
    return lhs.event_sequence.length() > rhs.event_sequence.length() &&
           lhs.score > rhs.score;
  });

  return sorted_triggers;
}

std::string EncodeEvents(const UserActivityEventList& events) {
  std::vector<UserActivityEventType> eligible_events;
  eligible_events.reserve(events.size());

  std::transform(events.cbegin(), events.cend(),
                 std::back_inserter(eligible_events),
                 [](const auto& event) { return event.type; });

  const std::string encoded_eligible_events =
      base::HexEncode(eligible_events.data(), eligible_events.size());

  return base::ToUpperASCII(encoded_eligible_events);
}

double CalculateScore(const UserActivityTriggerList& triggers,
                      const std::string& events) {
  std::string mutable_events(events);

  double score = 0.0;

  for (const auto& trigger : triggers) {
    std::string::size_type pos = 0;

    for (;;) {
      pos = mutable_events.find(trigger.event_sequence, pos);
      if (pos == std::string::npos) {
        break;
      }

      if (pos % 2 != 0) {
        // Event sequences start on hex/byte character boundaries
        ++pos;
        continue;
      }

      mutable_events.erase(pos, trigger.event_sequence.length());
      score += trigger.score;
    }
  }

  return score;
}

}  // namespace

double GetUserActivityScore(const UserActivityTriggerList& triggers,
                            const UserActivityEventList& events) {
  if (triggers.empty() || events.empty()) {
    return 0.0;
  }

  const UserActivityTriggerList sorted_triggers = SortTriggers(triggers);

  const std::string encoded_events = EncodeEvents(events);

  return CalculateScore(sorted_triggers, encoded_events);
}

}  // namespace brave_ads
