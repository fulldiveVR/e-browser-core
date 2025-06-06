/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/settings/settings.h"

#include "base/test/scoped_feature_list.h"
#include "brave/components/brave_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "brave/components/brave_ads/core/internal/common/test/test_base.h"
#include "brave/components/brave_ads/core/internal/settings/settings_test_util.h"
#include "brave/components/brave_ads/core/public/ad_units/notification_ad/notification_ad_feature.h"
#include "brave/components/brave_ads/core/public/prefs/pref_names.h"

// npm run test -- brave_unit_tests --filter=BraveAds*

namespace brave_ads {

class BraveAdsSettingsTest : public test::TestBase {};

TEST_F(BraveAdsSettingsTest, UserHasJoinedBraveRewards) {
  // Act & Assert
  EXPECT_TRUE(UserHasJoinedBraveRewards());
}

TEST_F(BraveAdsSettingsTest, UserHasNotJoinedBraveRewards) {
  // Arrange
  test::DisableBraveRewards();

  // Act & Assert
  EXPECT_FALSE(UserHasJoinedBraveRewards());
}

TEST_F(BraveAdsSettingsTest, UserHasJoinedBraveRewardsAndConnectedWallet) {
  // Act & Assert
  EXPECT_TRUE(UserHasJoinedBraveRewardsAndConnectedWallet());
}

TEST_F(BraveAdsSettingsTest, UserHasJoinedBraveRewardsAndNotConnectedWallet) {
  // Arrange
  test::DisconnectExternalBraveRewardsWallet();

  // Act & Assert
  EXPECT_FALSE(UserHasJoinedBraveRewardsAndConnectedWallet());
}

TEST_F(BraveAdsSettingsTest, UserHasOptedInToBraveNewsAds) {
  // Act & Assert
  EXPECT_TRUE(UserHasOptedInToBraveNewsAds());
}

TEST_F(BraveAdsSettingsTest, UserHasNotOptedInToBraveNews) {
  // Arrange
  test::OptOutOfBraveNewsAds();

  // Act & Assert
  EXPECT_FALSE(UserHasOptedInToBraveNewsAds());
}

TEST_F(BraveAdsSettingsTest, UserHasOptedInToNewTabPageAds) {
  // Act & Assert
  EXPECT_TRUE(UserHasOptedInToNewTabPageAds());
}

TEST_F(BraveAdsSettingsTest, UserHasNotOptedInToNewTabPageAds) {
  // Arrange
  test::OptOutOfNewTabPageAds();

  // Act & Assert
  EXPECT_FALSE(UserHasOptedInToNewTabPageAds());
}

TEST_F(BraveAdsSettingsTest, UserHasOptedInToNotificationAds) {
  // Act & Assert
  EXPECT_TRUE(UserHasOptedInToNotificationAds());
}

TEST_F(BraveAdsSettingsTest, UserHasNotOptedInToNotificationAds) {
  // Arrange
  test::OptOutOfNotificationAds();

  // Act & Assert
  EXPECT_FALSE(UserHasOptedInToNotificationAds());
}

TEST_F(BraveAdsSettingsTest, MaximumNotificationAdsPerHour) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kNotificationAdFeature, {{"default_ads_per_hour", "2"}});

  test::SetProfileInt64PrefValue(prefs::kMaximumNotificationAdsPerHour, 3);

  // Act & Assert
  EXPECT_EQ(3, GetMaximumNotificationAdsPerHour());
}

TEST_F(BraveAdsSettingsTest, DefaultMaximumNotificationAdsPerHour) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kNotificationAdFeature, {{"default_ads_per_hour", "2"}});

  // Act & Assert
  EXPECT_EQ(2, GetMaximumNotificationAdsPerHour());
}

TEST_F(BraveAdsSettingsTest, UserHasOptedInToSearchResultAds) {
  // Act & Assert
  EXPECT_TRUE(UserHasOptedInToSearchResultAds());
}

TEST_F(BraveAdsSettingsTest, UserHasNotOptedInToSearchResultAds) {
  // Arrange
  test::OptOutOfSearchResultAds();

  // Act & Assert
  EXPECT_FALSE(UserHasOptedInToSearchResultAds());
}

}  // namespace brave_ads
