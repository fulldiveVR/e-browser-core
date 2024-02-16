// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BRAVE_COMPONENTS_BRAVE_ADAPTIVE_CAPTCHA_PREF_NAMES_H_
#define BRAVE_COMPONENTS_BRAVE_ADAPTIVE_CAPTCHA_PREF_NAMES_H_

namespace brave_adaptive_captcha {
namespace prefs {

inline constexpr char kScheduledCaptchaId[] =
    "aiwize.rewards.scheduled_captcha.id";
inline constexpr char kScheduledCaptchaPaymentId[] =
    "aiwize.rewards.scheduled_captcha.payment_id";
inline constexpr char kScheduledCaptchaSnoozeCount[] =
    "aiwize.rewards.scheduled_captcha.snooze_count";
inline constexpr char kScheduledCaptchaFailedAttempts[] =
    "aiwize.rewards.scheduled_captcha.failed_attempts";
inline constexpr char kScheduledCaptchaPaused[] =
    "aiwize.rewards.scheduled_captcha.paused";

}  // namespace prefs
}  // namespace brave_adaptive_captcha

#endif  // BRAVE_COMPONENTS_BRAVE_ADAPTIVE_CAPTCHA_PREF_NAMES_H_
