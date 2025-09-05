/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/ntp_background_images/browser/ntp_sponsored_images_data.h"

#include "base/check.h"
#include "base/files/file_path.h"
#include "base/logging.h"
#include "base/strings/string_util.h"
#include "base/strings/stringprintf.h"
#include "base/time/time_delta_from_string.h"
#include "base/uuid.h"
#include "brave/components/constants/webui_url_constants.h"
#include "brave/components/ntp_background_images/browser/url_constants.h"
#include "content/public/common/url_constants.h"

namespace ntp_background_images {


TopSite::TopSite() = default;
TopSite::TopSite(const std::string& i_name,
                 const std::string& i_destination_url,
                 const std::string& i_image_path,
                 const base::FilePath& i_image_file)
    : name(i_name),
      destination_url(i_destination_url),
      image_path(i_image_path),
      image_file(i_image_file) {}

TopSite::TopSite(const TopSite& other) = default;

TopSite& TopSite::operator=(const TopSite& other) = default;

TopSite::TopSite(TopSite&& other) noexcept = default;

TopSite& TopSite::operator=(TopSite&& other) noexcept = default;

TopSite::~TopSite() = default;

bool TopSite::IsValid() const {
  return !name.empty() && !destination_url.empty() && !image_file.empty();
}

Logo::Logo() = default;

Logo::Logo(const Logo& other) = default;

Logo& Logo::operator=(const Logo& other) = default;

Logo::Logo(Logo&& other) noexcept = default;

Logo& Logo::operator=(Logo&& other) noexcept = default;

Logo::~Logo() = default;

Creative::Creative() = default;
Creative::Creative(WallpaperType wallpaper_type,
                   const base::FilePath& file_path,
                   const gfx::Point& point,
                   const Logo& test_logo,
                   const std::string& creative_instance_id)
    : wallpaper_type(wallpaper_type),
      file_path(file_path),
      focal_point(point),
      creative_instance_id(creative_instance_id),
      logo(test_logo) {}

Creative::Creative(const Creative& other) = default;

Creative& Creative::operator=(const Creative& other) = default;

Creative::Creative(Creative&& other) noexcept = default;

Creative& Creative::operator=(Creative&& other) noexcept = default;

Creative::~Creative() = default;

Campaign::Campaign() = default;

Campaign::Campaign(const Campaign&) = default;

Campaign& Campaign::operator=(const Campaign&) = default;

Campaign::Campaign(Campaign&& other) noexcept = default;

Campaign& Campaign::operator=(Campaign&& other) noexcept = default;

Campaign::~Campaign() = default;

bool Campaign::IsValid() const {
  return !creatives.empty();
}

NTPSponsoredImagesData::NTPSponsoredImagesData() = default;
NTPSponsoredImagesData::NTPSponsoredImagesData(
    const base::Value::Dict& dict,
    const base::FilePath& installed_dir)
    : NTPSponsoredImagesData() {

}

NTPSponsoredImagesData::NTPSponsoredImagesData(
    const NTPSponsoredImagesData& data) = default;

NTPSponsoredImagesData& NTPSponsoredImagesData::operator=(
    const NTPSponsoredImagesData& data) = default;

NTPSponsoredImagesData::NTPSponsoredImagesData(
    NTPSponsoredImagesData&& other) noexcept = default;

NTPSponsoredImagesData& NTPSponsoredImagesData::operator=(
    NTPSponsoredImagesData&& other) noexcept = default;

NTPSponsoredImagesData::~NTPSponsoredImagesData() = default;

void NTPSponsoredImagesData::ParseCampaigns(
    const base::Value::List& list,
    const base::FilePath& installed_dir) {

}

std::optional<Campaign> NTPSponsoredImagesData::MaybeParseCampaign(
    const base::Value::Dict& dict,
    const base::FilePath& installed_dir) {
  return std::nullopt;
}

void NTPSponsoredImagesData::ParseSuperReferrals(
    const base::Value::Dict& dict,
    const base::FilePath& installed_dir) {

}

bool NTPSponsoredImagesData::IsValid() const {
  return false;
}

bool NTPSponsoredImagesData::IsSuperReferral() const {
  return false;
}

std::optional<base::Value::Dict> NTPSponsoredImagesData::MaybeGetBackgroundAt(
    size_t campaign_index,
    size_t creative_index) const {
  return {};
}


}  // namespace ntp_background_images
