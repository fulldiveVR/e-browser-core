/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/serving/prediction/model_based/input_variable/creative_ad_model_based_predictor_input_variable.h"

#include "brave/components/brave_ads/core/internal/creatives/creative_ad_info.h"
#include "brave/components/brave_ads/core/internal/serving/prediction/model_based/input_variable/creative_ad_model_based_predictor_input_variable_info.h"
#include "brave/components/brave_ads/core/internal/serving/prediction/model_based/input_variable/creative_ad_model_based_predictor_input_variable_util.h"
#include "brave/components/brave_ads/core/internal/serving/prediction/model_based/weight/creative_ad_model_based_predictor_weights_info.h"

namespace brave_ads {

CreativeAdModelBasedPredictorInputVariableInfo
ComputeCreativeAdModelBasedPredictorInputVariable(
    const CreativeAdInfo& creative_ad,
    const UserModelInfo& user_model,
    const AdEventList& ad_events,
    const CreativeAdModelBasedPredictorWeightsInfo& weights) {
  CreativeAdModelBasedPredictorInputVariableInfo input_variable;

  input_variable.intent_segment =
      ComputeCreativeAdModelBasedPredictorIntentSegmentInputVariable(
          user_model, creative_ad.segment, weights);

  input_variable.latent_interest_segment =
      ComputeCreativeAdModelBasedPredictorLatentInterestSegmentInputVariable(
          user_model, creative_ad.segment, weights);

  input_variable.interest_segment =
      ComputeCreativeAdModelBasedPredictorInterestSegmentInputVariable(
          user_model, creative_ad.segment, weights);

  input_variable.last_seen_ad =
      ComputeCreativeAdModelBasedPredictorLastSeenAdInputVariable(
          creative_ad, ad_events, weights);

  input_variable.last_seen_advertiser =
      ComputeCreativeAdModelBasedPredictorLastSeenAdvertiserInputVariable(
          creative_ad, ad_events, weights);

  return input_variable;
}

}  // namespace brave_ads
