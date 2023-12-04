/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_CREATIVE_AD_MODEL_BASED_PREDICTOR_INPUT_VARIABLE_UTIL_H_
#define BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_CREATIVE_AD_MODEL_BASED_PREDICTOR_INPUT_VARIABLE_UTIL_H_

#include <string>

#include "brave/components/brave_ads/core/internal/user_engagement/ad_events/ad_event_info.h"

namespace brave_ads {

struct CreativeAdModelBasedPredictorLastSeenInputVariableInfo;
struct CreativeAdModelBasedPredictorSegmentInputVariablesInfo;
struct CreativeAdModelBasedPredictorWeightsInfo;
struct UserModelInfo;
struct CreativeAdInfo;

CreativeAdModelBasedPredictorSegmentInputVariablesInfo
ComputeCreativeAdModelBasedPredictorIntentSegmentInputVariable(
    const UserModelInfo& user_model,
    const std::string& segment,
    const CreativeAdModelBasedPredictorWeightsInfo& weights);

CreativeAdModelBasedPredictorSegmentInputVariablesInfo
ComputeCreativeAdModelBasedPredictorLatentInterestSegmentInputVariable(
    const UserModelInfo& user_model,
    const std::string& segment,
    const CreativeAdModelBasedPredictorWeightsInfo& weights);

CreativeAdModelBasedPredictorSegmentInputVariablesInfo
ComputeCreativeAdModelBasedPredictorInterestSegmentInputVariable(
    const UserModelInfo& user_model,
    const std::string& segment,
    const CreativeAdModelBasedPredictorWeightsInfo& weights);

CreativeAdModelBasedPredictorLastSeenInputVariableInfo
ComputeCreativeAdModelBasedPredictorLastSeenAdInputVariable(
    const CreativeAdInfo& creative_ad,
    const AdEventList& ad_events,
    const CreativeAdModelBasedPredictorWeightsInfo& weights);

CreativeAdModelBasedPredictorLastSeenInputVariableInfo
ComputeCreativeAdModelBasedPredictorLastSeenAdvertiserInputVariable(
    const CreativeAdInfo& creative_ad,
    const AdEventList& ad_events,
    const CreativeAdModelBasedPredictorWeightsInfo& weights);

}  // namespace brave_ads

#endif  // BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_SERVING_PREDICTION_MODEL_BASED_INPUT_VARIABLE_CREATIVE_AD_MODEL_BASED_PREDICTOR_INPUT_VARIABLE_UTIL_H_
