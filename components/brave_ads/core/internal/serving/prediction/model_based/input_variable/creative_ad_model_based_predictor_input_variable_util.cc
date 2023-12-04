/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/serving/prediction/model_based/input_variable/creative_ad_model_based_predictor_input_variable_util.h"

#include "base/containers/contains.h"
#include "brave/components/brave_ads/core/internal/segments/segment_alias.h"
#include "brave/components/brave_ads/core/internal/segments/segment_util.h"
#include "brave/components/brave_ads/core/internal/serving/eligible_ads/allocation/seen_ads_util.h"
#include "brave/components/brave_ads/core/internal/serving/eligible_ads/allocation/seen_advertisers_util.h"
#include "brave/components/brave_ads/core/internal/serving/eligible_ads/eligible_ads_constants.h"
#include "brave/components/brave_ads/core/internal/serving/prediction/model_based/input_variable/last_seen/creative_ad_model_based_predictor_last_seen_input_variable_info.h"
#include "brave/components/brave_ads/core/internal/serving/prediction/model_based/input_variable/segment/creative_ad_model_based_predictor_segment_input_variables_info.h"
#include "brave/components/brave_ads/core/internal/serving/prediction/model_based/weight/creative_ad_model_based_predictor_weights_info.h"
#include "brave/components/brave_ads/core/internal/serving/targeting/segments/top_user_model_segments.h"

namespace brave_ads {

namespace {

CreativeAdModelBasedPredictorSegmentInputVariablesInfo
ComputeSegmentInputVariable(
    const SegmentList& top_child_segments,
    const SegmentList& top_parent_segments,
    const std::string& segment,
    const CreativeAdModelBasedPredictorWeightsInfo& weights) {
  CreativeAdModelBasedPredictorSegmentInputVariablesInfo segment_input_variable;

  if (segment == kUntargetedSegment) {
    segment_input_variable.untargeted_matches.value = true;
    segment_input_variable.untargeted_matches.weight =
        weights.untargeted_segment;
  } else {
    // TODO(tmancey): Discuss with Terry James.
    segment_input_variable.child_matches.value =
        base::Contains(top_child_segments, segment);
    segment_input_variable.child_matches.weight = weights.intent_segment.child;

    segment_input_variable.parent_matches.value =
        base::Contains(top_parent_segments, GetParentSegment(segment));
    segment_input_variable.parent_matches.weight =
        weights.intent_segment.parent;
  }

  return segment_input_variable;
}

}  // namespace

CreativeAdModelBasedPredictorSegmentInputVariablesInfo
ComputeCreativeAdModelBasedPredictorIntentSegmentInputVariable(
    const UserModelInfo& user_model,
    const std::string& segment,
    const CreativeAdModelBasedPredictorWeightsInfo& weights) {
  return ComputeSegmentInputVariable(GetTopChildIntentSegments(user_model),
                                     GetTopParentIntentSegments(user_model),
                                     segment, weights);
}

CreativeAdModelBasedPredictorSegmentInputVariablesInfo
ComputeCreativeAdModelBasedPredictorLatentInterestSegmentInputVariable(
    const UserModelInfo& user_model,
    const std::string& segment,
    const CreativeAdModelBasedPredictorWeightsInfo& weights) {
  return ComputeSegmentInputVariable(
      GetTopChildLatentInterestSegments(user_model),
      GetTopParentLatentInterestSegments(user_model), segment, weights);
}

CreativeAdModelBasedPredictorSegmentInputVariablesInfo
ComputeCreativeAdModelBasedPredictorInterestSegmentInputVariable(
    const UserModelInfo& user_model,
    const std::string& segment,
    const CreativeAdModelBasedPredictorWeightsInfo& weights) {
  return ComputeSegmentInputVariable(GetTopChildInterestSegments(user_model),
                                     GetTopParentInterestSegments(user_model),
                                     segment, weights);
}

CreativeAdModelBasedPredictorLastSeenInputVariableInfo
ComputeCreativeAdModelBasedPredictorLastSeenAdInputVariable(
    const CreativeAdInfo& creative_ad,
    const AdEventList& ad_events,
    const CreativeAdModelBasedPredictorWeightsInfo& weights) {
  CreativeAdModelBasedPredictorLastSeenInputVariableInfo
      last_seen_ad_input_variable;

  const std::optional<base::Time> last_seen_at =
      GetLastSeenAdAt(ad_events, creative_ad);
  if (last_seen_at) {
    last_seen_ad_input_variable.value = base::Time::Now() - *last_seen_at;
  }

  last_seen_ad_input_variable.weight = weights.last_seen_ad;

  return last_seen_ad_input_variable;
}

CreativeAdModelBasedPredictorLastSeenInputVariableInfo
ComputeCreativeAdModelBasedPredictorLastSeenAdvertiserInputVariable(
    const CreativeAdInfo& creative_ad,
    const AdEventList& ad_events,
    const CreativeAdModelBasedPredictorWeightsInfo& weights) {
  CreativeAdModelBasedPredictorLastSeenInputVariableInfo
      last_seen_advertiser_input_variable;

  const std::optional<base::Time> last_seen_at =
      GetLastSeenAdvertiserAt(ad_events, creative_ad);
  if (last_seen_at) {
    last_seen_advertiser_input_variable.value =
        base::Time::Now() - *last_seen_at;
  }

  last_seen_advertiser_input_variable.weight = weights.last_seen_advertiser;

  return last_seen_advertiser_input_variable;
}

}  // namespace brave_ads
