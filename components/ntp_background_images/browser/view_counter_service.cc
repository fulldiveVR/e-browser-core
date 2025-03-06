// Copyright (c) 2020 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "brave/components/ntp_background_images/browser/view_counter_service.h"

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "base/check_is_test.h"
#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "base/logging.h"
#include "base/metrics/histogram_macros.h"
#include "brave/components/ntp_background_images/browser/brave_ntp_custom_background_service.h"
#include "brave/components/ntp_background_images/browser/ntp_background_images_data.h"
#include "brave/components/ntp_background_images/browser/ntp_p3a_helper.h"
#include "brave/components/ntp_background_images/browser/ntp_p3a_util.h"
#include "brave/components/ntp_background_images/browser/ntp_sponsored_images_data.h"
#include "brave/components/ntp_background_images/browser/url_constants.h"
#include "brave/components/ntp_background_images/common/pref_names.h"
#include "brave/components/p3a_utils/bucket.h"
#include "brave/components/time_period_storage/weekly_storage.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/web_ui_data_source.h"
#include "url/gurl.h"

#if BUILDFLAG(ENABLE_CUSTOM_BACKGROUND)
#endif

namespace ntp_background_images {

namespace {

constexpr char kNewTabsCreated[] = "brave.new_tab_page.p3a_new_tabs_created";
constexpr char kSponsoredNewTabsCreated[] =
    "brave.new_tab_page.p3a_sponsored_new_tabs_created";

constexpr char kNewTabsCreatedHistogramName[] = "Brave.NTP.NewTabsCreated.3";
constexpr int kNewTabsCreatedMetricBuckets[] = {0, 1, 2, 3, 4, 8, 15};
constexpr char kSponsoredNewTabsHistogramName[] =
    "Brave.NTP.SponsoredNewTabsCreated.2";
constexpr int kSponsoredNewTabsBuckets[] = {0, 10, 20, 30, 40, 50};

// Obsolete pref
constexpr char kObsoleteCountToBrandedWallpaperPref[] =
    "brave.count_to_branded_wallpaper";

constexpr base::TimeDelta kP3AReportInterval = base::Days(1);

}  // namespace

// static
void ViewCounterService::RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  registry->RegisterListPref(kNewTabsCreated);
  registry->RegisterListPref(kSponsoredNewTabsCreated);
}

void ViewCounterService::RegisterProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterBooleanPref(prefs::kBrandedWallpaperNotificationDismissed,
                                false);
  registry->RegisterBooleanPref(
      prefs::kNewTabPageShowSponsoredImagesBackgroundImage, true);
  // Integer type is used because this pref is used by radio button group in
  // appearance settings. Super referral is disabled when it is set to DEFAULT.
  registry->RegisterIntegerPref(
      prefs::kNewTabPageSuperReferralThemesOption, SUPER_REFERRAL);
  registry->RegisterBooleanPref(
      prefs::kNewTabPageShowBackgroundImage, true);
}

void ViewCounterService::RegisterProfilePrefsForMigration(
    user_prefs::PrefRegistrySyncable* registry) {
  // Added 09/2023
  registry->RegisterIntegerPref(kObsoleteCountToBrandedWallpaperPref, 0);
}

void ViewCounterService::MigrateObsoleteProfilePrefs(PrefService* prefs) {
  // Added 09/2023
  prefs->ClearPref(kObsoleteCountToBrandedWallpaperPref);
}

ViewCounterService::ViewCounterService(
    NTPBackgroundImagesService* background_images_service,
    BraveNTPCustomBackgroundService* custom_background_service,
    PrefService* prefs,
    PrefService* local_state,
    std::unique_ptr<NTPP3AHelper> ntp_p3a_helper,
    bool is_supported_locale)
    : background_images_service_(background_images_service),
      prefs_(prefs),
      local_state_prefs_(local_state),
      is_supported_locale_(is_supported_locale),
      model_(prefs),
      custom_background_service_(custom_background_service),
      ntp_p3a_helper_(std::move(ntp_p3a_helper)) {
  DCHECK(background_images_service_);
  ntp_background_images_service_observation_.Observe(
      background_images_service_);

  new_tab_count_state_ =
      std::make_unique<WeeklyStorage>(local_state, kNewTabsCreated);
  branded_new_tab_count_state_ =
      std::make_unique<WeeklyStorage>(local_state, kSponsoredNewTabsCreated);

  ResetModel();

  pref_change_registrar_.Init(prefs_);
  pref_change_registrar_.Add(
      prefs::kNewTabPageSuperReferralThemesOption,
      base::BindRepeating(&ViewCounterService::OnPreferenceChanged,
                          weak_ptr_factory_.GetWeakPtr()));
  pref_change_registrar_.Add(
      prefs::kNewTabPageShowSponsoredImagesBackgroundImage,
      base::BindRepeating(&ViewCounterService::OnPreferenceChanged,
                          weak_ptr_factory_.GetWeakPtr()));
  pref_change_registrar_.Add(
      prefs::kNewTabPageShowBackgroundImage,
      base::BindRepeating(&ViewCounterService::OnPreferenceChanged,
                          weak_ptr_factory_.GetWeakPtr()));

  OnBackgroundImagesDataDidUpdate(GetCurrentWallpaperData());
  OnSponsoredImagesDataDidUpdate(GetCurrentBrandedWallpaperData());

  UpdateP3AValues();
}

ViewCounterService::~ViewCounterService() = default;

void ViewCounterService::BrandedWallpaperWillBeDisplayed(
    const std::string& wallpaper_id,
    const std::string& creative_instance_id,
    const std::string& campaign_id) {

}

NTPBackgroundImagesData* ViewCounterService::GetCurrentWallpaperData() const {
  return background_images_service_->GetBackgroundImagesData();
}

NTPSponsoredImagesData* ViewCounterService::GetCurrentBrandedWallpaperData()
    const {
  NTPSponsoredImagesData* const images_data =
      background_images_service_->GetBrandedImagesData(/*super_referral=*/true);
  if (images_data && IsSuperReferralWallpaperOptedIn()) {
    return images_data;
  }

  return background_images_service_->GetBrandedImagesData(
      /*super_referral=*/false);
}

std::optional<base::Value::Dict>
ViewCounterService::GetNextWallpaperForDisplay() {
  model_.RotateBackgroundWallpaperImageIndex();
  return GetCurrentWallpaper();
}

std::optional<base::Value::Dict>
ViewCounterService::GetCurrentWallpaperForDisplay() {
  if (!ShouldShowBrandedWallpaper()) {
    return GetCurrentWallpaper();
  }

  if (std::optional<base::Value::Dict> branded_wallpaper =
          GetCurrentBrandedWallpaper()) {
    current_wallpaper_ = branded_wallpaper->Clone();
    return branded_wallpaper;
  }

  // The retrieval of `branded_wallpaper` failed due to frequency capping. In
  // such instances, we need to ensure the next wallpaper is displayed because
  // it would not have been incremented during the last `RegisterPageView` call.
  return GetNextWallpaperForDisplay();
}

std::optional<base::Value::Dict> ViewCounterService::GetCurrentWallpaper()
    const {
  if (!IsBackgroundWallpaperActive()) {
    return std::nullopt;
  }

#if BUILDFLAG(ENABLE_CUSTOM_BACKGROUND)
  if (ShouldShowCustomBackground()) {
    if (auto background = custom_background_service_->GetBackground();
        !background.empty()) {
      return background;
    }
  }
#endif

  const NTPBackgroundImagesData* const images_data = GetCurrentWallpaperData();
  if (!images_data) {
    CHECK_IS_TEST();
    return std::nullopt;
  }

  return images_data->GetBackgroundAt(model_.current_wallpaper_image_index())
      .Set(kWallpaperRandomKey, true);
}

std::optional<base::Value::Dict>
ViewCounterService::GetCurrentBrandedWallpaper() {
    return std::nullopt;
}

void ViewCounterService::GetCurrentBrandedWallpaper(
    base::OnceCallback<
        void(const std::optional<GURL>& url,
             const std::optional<std::string>& placement_id,
             const std::optional<std::string>& creative_instance_id,
             const std::optional<GURL>& target_url)> callback) const {
  auto failed = [&callback]() {
    std::move(callback).Run(/*url=*/std::nullopt,
                            /*placement_id=*/std::nullopt,
                            /*creative_instance_id=*/std::nullopt,
                            /*target_url=*/std::nullopt);
  };

  if (!current_wallpaper_) {
    return failed();
  }

  const std::string* const url =
      current_wallpaper_->FindString(ntp_background_images::kWallpaperURLKey);
  if (!url) {
    return failed();
  }

  const std::string* const creative_instance_id =
      current_wallpaper_->FindString(
          ntp_background_images::kCreativeInstanceIDKey);
  if (!creative_instance_id) {
    return failed();
  }

  const std::string* const placement_id =
      current_wallpaper_->FindString(ntp_background_images::kWallpaperIDKey);
  if (!placement_id) {
    return failed();
  }

  const std::string* const target_url =
      current_wallpaper_->FindStringByDottedPath(
          ntp_background_images::kLogoDestinationURLPath);
  if (!target_url) {
    return failed();
  }

  std::move(callback).Run(GURL(*url), *placement_id, *creative_instance_id,
                          GURL(*target_url));
}


std::optional<base::Value::Dict>
ViewCounterService::GetNextBrandedWallpaperWhichMatchesConditions() {
    return std::nullopt;
}

std::optional<base::Value::Dict>
ViewCounterService::GetCurrentBrandedWallpaperFromAdInfo() const {
    return std::nullopt;
}

std::optional<base::Value::Dict>
ViewCounterService::GetCurrentBrandedWallpaperFromModel() const {
  size_t current_campaign_index;
  size_t current_creative_index;
  std::tie(current_campaign_index, current_creative_index) =
      model_.GetCurrentBrandedImageIndex();
  return GetCurrentBrandedWallpaperData()->GetBackgroundAt(
      current_campaign_index, current_creative_index);
}

std::vector<TopSite> ViewCounterService::GetTopSitesData() const {
  if (const NTPSponsoredImagesData* const images_data =
          GetCurrentBrandedWallpaperData()) {
    return images_data->top_sites;
  }

  return {};
}

void ViewCounterService::Shutdown() {
  ntp_background_images_service_observation_.Reset();
}

void ViewCounterService::OnBackgroundImagesDataDidUpdate(
    NTPBackgroundImagesData* data) {
  if (data) {
    DVLOG(2) << __func__ << ": NTP BI component is updated.";
    ResetModel();
  }
}

void ViewCounterService::OnSponsoredImagesDataDidUpdate(
    NTPSponsoredImagesData* data) {
  if (data) {
    DVLOG(2) << __func__ << ": NTP SI/SR component is updated.";
    ResetModel();
  }
}

void ViewCounterService::OnSponsoredContentDidUpdate(
    const base::Value::Dict& data) {

}

void ViewCounterService::OnSuperReferralCampaignDidEnd() {
  // Need to reset model because SI images are shown only for every 4th NTP but
  // we've shown SR images for every NTP.
  ResetModel();
}

void ViewCounterService::ParseAndSaveCreativeNewTabPageAdsCallback(
    bool success) {
  if (success) {
    MaybePrefetchNewTabPageAd();
  }
}

void ViewCounterService::ResetModel() {
  model_.Reset();

  model_.set_show_branded_wallpaper(IsSponsoredImagesWallpaperOptedIn());
  model_.set_show_wallpaper(
      prefs_->GetBoolean(prefs::kNewTabPageShowBackgroundImage));

  if (const NTPSponsoredImagesData* const images_data =
          GetCurrentBrandedWallpaperData()) {
    std::vector<size_t> campaigns_total_branded_images_count;
    campaigns_total_branded_images_count.reserve(images_data->campaigns.size());
    for (const auto& campaign : images_data->campaigns) {
      campaigns_total_branded_images_count.push_back(campaign.creatives.size());
    }
    model_.set_always_show_branded_wallpaper(images_data->IsSuperReferral());
    model_.SetCampaignsTotalBrandedImageCount(
        campaigns_total_branded_images_count);
  }

  if (const NTPBackgroundImagesData* const images_data =
          GetCurrentWallpaperData()) {
    model_.set_total_image_count(
        static_cast<int>(images_data->backgrounds.size()));
  }
}

void ViewCounterService::OnPreferenceChanged(const std::string& pref_name) {

  if (pref_name == prefs::kNewTabPageShowBackgroundImage ||
      pref_name == prefs::kNewTabPageShowSponsoredImagesBackgroundImage) {
    RecordSponsoredImagesEnabledP3A(prefs_);
  }

  // Reset model because SI and SR use different policy.
  // Start from initial model state whenever
  // prefs::kNewTabPageSuperReferralThemesOption or
  // prefs::kNewTabPageShowSponsoredImagesBackgroundImage prefs are changed.
  ResetModel();
}

void ViewCounterService::ResetNotificationState() {
  prefs_->SetBoolean(prefs::kBrandedWallpaperNotificationDismissed, false);
}

void ViewCounterService::RegisterPageView() {
  new_tab_count_state_->AddDelta(1);
  UpdateP3AValues();
  // This will be no-op when component is not ready.
  background_images_service_->MaybeCheckForSponsoredComponentUpdate();
  model_.RegisterPageView();
  MaybePrefetchNewTabPageAd();
}

void ViewCounterService::BrandedWallpaperLogoClicked(
    const std::string& creative_instance_id,
    const std::string& /*destination_url*/,
    const std::string& wallpaper_id) {

}


bool ViewCounterService::ShouldShowBrandedWallpaper() const {
  return IsBrandedWallpaperActive() && model_.ShouldShowBrandedWallpaper();
}

bool ViewCounterService::ShouldShowCustomBackground() const {
#if BUILDFLAG(ENABLE_CUSTOM_BACKGROUND)
  return custom_background_service_ &&
         custom_background_service_->ShouldShowCustomBackground();
#else
  return false;
#endif
}

void ViewCounterService::InitializeWebUIDataSource(
    content::WebUIDataSource* html_source) {
  html_source->AddString("superReferralThemeName", GetSuperReferralThemeName());
}

void ViewCounterService::OnTabURLChanged(const GURL& url) {
  if (ntp_p3a_helper_) {
    ntp_p3a_helper_->SetLastTabURL(url);
  }
}

bool ViewCounterService::IsBrandedWallpaperActive() const {
  if (!GetCurrentBrandedWallpaperData()) {
    return false;
  }

  // We show SR regardless of ntp background images option because SR works
  // like theme.
  if (GetCurrentBrandedWallpaperData()->IsSuperReferral() &&
      IsSuperReferralWallpaperOptedIn()) {
    return true;
  }

  // We don't show SI if user disables bg image.
  if (!prefs_->GetBoolean(prefs::kNewTabPageShowBackgroundImage)) {
    return false;
  }

  return IsSponsoredImagesWallpaperOptedIn();
}

bool ViewCounterService::IsBackgroundWallpaperActive() const {
#if !BUILDFLAG(IS_ANDROID)
  if (!prefs_->GetBoolean(prefs::kNewTabPageShowBackgroundImage)) {
    return false;
  }
#endif

  return !!GetCurrentWallpaperData() || ShouldShowCustomBackground();
}

bool ViewCounterService::IsSponsoredImagesWallpaperOptedIn() const {
  return prefs_->GetBoolean(
      prefs::kNewTabPageShowSponsoredImagesBackgroundImage) &&
        is_supported_locale_;
}

bool ViewCounterService::IsSuperReferralWallpaperOptedIn() const {
  return prefs_->GetInteger(prefs::kNewTabPageSuperReferralThemesOption) ==
             SUPER_REFERRAL;
}

bool ViewCounterService::IsSuperReferral() const {
  return background_images_service_->IsSuperReferral();
}

std::string ViewCounterService::GetSuperReferralThemeName() const {
  return background_images_service_->GetSuperReferralThemeName();
}

std::string ViewCounterService::GetSuperReferralCode() const {
  return background_images_service_->GetSuperReferralCode();
}

void ViewCounterService::MaybePrefetchNewTabPageAd() {

}

void ViewCounterService::UpdateP3AValues() {
  uint64_t new_tab_count = new_tab_count_state_->GetHighestValueInWeek();
  p3a_utils::RecordToHistogramBucket(kNewTabsCreatedHistogramName,
                                     kNewTabsCreatedMetricBuckets,
                                     static_cast<int>(new_tab_count));

  uint64_t branded_new_tab_count =
      branded_new_tab_count_state_->GetHighestValueInWeek();
  if (branded_new_tab_count == 0 || new_tab_count == 0) {
    UMA_HISTOGRAM_EXACT_LINEAR(kSponsoredNewTabsHistogramName, 0,
                               std::size(kSponsoredNewTabsBuckets) + 1);
  } else {
    double ratio = (static_cast<double>(branded_new_tab_count) /
                    static_cast<double>(new_tab_count)) *
                   100;
    p3a_utils::RecordToHistogramBucket(kSponsoredNewTabsHistogramName,
                                       kSponsoredNewTabsBuckets,
                                       static_cast<int>(ratio));
  }

  p3a_update_timer_.Start(FROM_HERE, base::Time::Now() + kP3AReportInterval,
                          base::BindOnce(&ViewCounterService::UpdateP3AValues,
                                         weak_ptr_factory_.GetWeakPtr()));
}

}  // namespace ntp_background_images
