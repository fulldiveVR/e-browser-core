/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/ads_impl.h"

#include <optional>
#include <utility>

#include "base/functional/bind.h"
#include "base/trace_event/trace_event.h"
#include "brave/components/brave_ads/core/internal/account/wallet/wallet_util.h"
#include "brave/components/brave_ads/core/internal/ads_client/ads_client_util.h"
#include "brave/components/brave_ads/core/internal/ads_core/ads_core_util.h"
#include "brave/components/brave_ads/core/internal/ads_internals/ads_internals_util.h"
#include "brave/components/brave_ads/core/internal/ads_notifier_manager.h"
#include "brave/components/brave_ads/core/internal/common/logging_util.h"
#include "brave/components/brave_ads/core/internal/creatives/notification_ads/notification_ad_manager.h"
#include "brave/components/brave_ads/core/internal/database/database_maintenance.h"
#include "brave/components/brave_ads/core/internal/database/database_manager.h"
#include "brave/components/brave_ads/core/internal/deprecated/client/client_state_manager.h"
#include "brave/components/brave_ads/core/internal/deprecated/confirmations/confirmation_state_manager.h"
#include "brave/components/brave_ads/core/internal/diagnostics/diagnostic_manager.h"
#include "brave/components/brave_ads/core/internal/history/ad_history_manager.h"
#include "brave/components/brave_ads/core/internal/legacy_migration/client/legacy_client_migration.h"
#include "brave/components/brave_ads/core/internal/legacy_migration/confirmations/legacy_confirmation_migration.h"
#include "brave/components/brave_ads/core/internal/legacy_migration/legacy_migration.h"
#include "brave/components/brave_ads/core/internal/user_engagement/ad_events/ad_events.h"
#include "brave/components/brave_ads/core/public/ads_client/ads_client.h"
#include "brave/components/brave_ads/core/public/ads_constants.h"
#include "brave/components/brave_ads/core/public/service/ads_service_callback.h"

namespace brave_ads {

AdsImpl::AdsImpl(AdsClient& ads_client,
                 const base::FilePath& database_path,
                 std::unique_ptr<TokenGeneratorInterface> token_generator)
    : global_state_(ads_client, database_path, std::move(token_generator)),
      database_maintenance_(std::make_unique<database::Maintenance>()) {}

AdsImpl::~AdsImpl() = default;

void AdsImpl::AddObserver(std::unique_ptr<AdsObserver> observer) {
  // `AdsNotifierManager` takes ownership of `observer`.
  AdsNotifierManager::GetInstance().AddObserver(std::move(observer));
}

void AdsImpl::SetSysInfo(mojom::SysInfoPtr mojom_sys_info) {
  GlobalState::GetInstance()->SysInfo().device_id = mojom_sys_info->device_id;
}

void AdsImpl::SetBuildChannel(mojom::BuildChannelInfoPtr mojom_build_channel) {
  auto& build_channel = GlobalState::GetInstance()->BuildChannel();
  build_channel.is_release = mojom_build_channel->is_release;
  build_channel.name = mojom_build_channel->name;
}

void AdsImpl::SetFlags(mojom::FlagsPtr mojom_flags) {
  auto& flags = GlobalState::GetInstance()->Flags();
  flags.should_debug = mojom_flags->should_debug;
  flags.did_override_from_command_line =
      mojom_flags->did_override_from_command_line;
  flags.environment_type = mojom_flags->environment_type;
}

void AdsImpl::SetContentSettings(
    mojom::ContentSettingsPtr mojom_content_settings) {
  auto& content_settings = GlobalState::GetInstance()->ContentSettings();
  content_settings.allow_javascript = mojom_content_settings->allow_javascript;
}

void AdsImpl::Initialize(mojom::WalletInfoPtr mojom_wallet,
                         InitializeCallback callback) {
  BLOG(1, "Initializing ads");

  TRACE_EVENT_NESTABLE_ASYNC_BEGIN0(kTraceEventCategory, "AdsImpl::Initialize",
                                    TRACE_ID_LOCAL(this));

  if (is_initialized_) {
    BLOG(0, "Already initialized ads");
    return FailedToInitialize(std::move(callback));
  }

  CreateOrOpenDatabase(std::move(mojom_wallet), std::move(callback));
}

void AdsImpl::Shutdown(ShutdownCallback callback) {
  if (!is_initialized_) {
    BLOG(0, "Shutdown failed as not initialized");
    return std::move(callback).Run(/*success=*/false);
  }

  NotificationAdManager::GetInstance().RemoveAll(/*should_close=*/true);

  DatabaseManager::GetInstance().Shutdown(std::move(callback));
}

void AdsImpl::GetInternals(GetInternalsCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(&AdsImpl::GetInternals,
                                          weak_factory_.GetWeakPtr(),
                                          std::move(callback)));
  }

  BuildAdsInternals(std::move(callback));
}

void AdsImpl::GetDiagnostics(GetDiagnosticsCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(&AdsImpl::GetDiagnostics,
                                          weak_factory_.GetWeakPtr(),
                                          std::move(callback)));
  }

  DiagnosticManager::GetInstance().GetDiagnostics(std::move(callback));
}

void AdsImpl::GetStatementOfAccounts(GetStatementOfAccountsCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(&AdsImpl::GetStatementOfAccounts,
                                          weak_factory_.GetWeakPtr(),
                                          std::move(callback)));
  }

  GetAccount().GetStatement(std::move(callback));
}

void AdsImpl::MaybeServeInlineContentAd(
    const std::string& dimensions,
    MaybeServeInlineContentAdCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(&AdsImpl::MaybeServeInlineContentAd,
                                          weak_factory_.GetWeakPtr(),
                                          dimensions, std::move(callback)));
  }

  GetAdHandler().MaybeServeInlineContentAd(dimensions, std::move(callback));
}

void AdsImpl::TriggerInlineContentAdEvent(
    const std::string& placement_id,
    const std::string& creative_instance_id,
    mojom::InlineContentAdEventType mojom_ad_event_type,
    TriggerAdEventCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(
        &AdsImpl::TriggerInlineContentAdEvent, weak_factory_.GetWeakPtr(),
        placement_id, creative_instance_id, mojom_ad_event_type,
        std::move(callback)));
  }

  GetAdHandler().TriggerInlineContentAdEvent(placement_id, creative_instance_id,
                                             mojom_ad_event_type,
                                             std::move(callback));
}

void AdsImpl::ParseAndSaveNewTabPageAds(
    base::Value::Dict dict,
    ParseAndSaveNewTabPageAdsCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(
        &AdsImpl::ParseAndSaveNewTabPageAds, weak_factory_.GetWeakPtr(),
        std::move(dict), std::move(callback)));
  }

  GetAdHandler().ParseAndSaveNewTabPageAds(std::move(dict),
                                           std::move(callback));
}

void AdsImpl::MaybeServeNewTabPageAd(MaybeServeNewTabPageAdCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(&AdsImpl::MaybeServeNewTabPageAd,
                                          weak_factory_.GetWeakPtr(),
                                          std::move(callback)));
  }

  GetAdHandler().MaybeServeNewTabPageAd(std::move(callback));
}

void AdsImpl::TriggerNewTabPageAdEvent(
    const std::string& placement_id,
    const std::string& creative_instance_id,
    bool should_metrics_fallback_to_p3a,
    mojom::NewTabPageAdEventType mojom_ad_event_type,
    TriggerAdEventCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(
        &AdsImpl::TriggerNewTabPageAdEvent, weak_factory_.GetWeakPtr(),
        placement_id, creative_instance_id, should_metrics_fallback_to_p3a,
        mojom_ad_event_type, std::move(callback)));
  }

  UpdateP3aMetricsFallbackState(creative_instance_id,
                                should_metrics_fallback_to_p3a);

  GetAdHandler().TriggerNewTabPageAdEvent(placement_id, creative_instance_id,
                                          mojom_ad_event_type,
                                          std::move(callback));
}

void AdsImpl::MaybeGetNotificationAd(const std::string& placement_id,
                                     MaybeGetNotificationAdCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(&AdsImpl::MaybeGetNotificationAd,
                                          weak_factory_.GetWeakPtr(),
                                          placement_id, std::move(callback)));
  }

  std::move(callback).Run(
      NotificationAdManager::GetInstance().MaybeGetForPlacementId(
          placement_id));
}

void AdsImpl::TriggerNotificationAdEvent(
    const std::string& placement_id,
    mojom::NotificationAdEventType mojom_ad_event_type,
    TriggerAdEventCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(
        &AdsImpl::TriggerNotificationAdEvent, weak_factory_.GetWeakPtr(),
        placement_id, mojom_ad_event_type, std::move(callback)));
  }

  GetAdHandler().TriggerNotificationAdEvent(placement_id, mojom_ad_event_type,
                                            std::move(callback));
}

void AdsImpl::TriggerPromotedContentAdEvent(
    const std::string& placement_id,
    const std::string& creative_instance_id,
    mojom::PromotedContentAdEventType mojom_ad_event_type,
    TriggerAdEventCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(
        &AdsImpl::TriggerPromotedContentAdEvent, weak_factory_.GetWeakPtr(),
        placement_id, creative_instance_id, mojom_ad_event_type,
        std::move(callback)));
  }

  GetAdHandler().TriggerPromotedContentAdEvent(
      placement_id, creative_instance_id, mojom_ad_event_type,
      std::move(callback));
}

void AdsImpl::MaybeGetSearchResultAd(const std::string& placement_id,
                                     MaybeGetSearchResultAdCallback callback) {
  if (task_queue_.should_queue()) {
    task_queue_.Add(base::BindOnce(&AdsImpl::MaybeGetSearchResultAd,
                                   weak_factory_.GetWeakPtr(), placement_id,
                                   std::move(callback)));
    return;
  }

  std::optional<mojom::CreativeSearchResultAdInfoPtr> ad =
      GetAdHandler().MaybeGetSearchResultAd(placement_id);
  std::move(callback).Run(ad ? std::move(*ad)
                             : mojom::CreativeSearchResultAdInfoPtr());
}

void AdsImpl::TriggerSearchResultAdEvent(
    mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad,
    mojom::SearchResultAdEventType mojom_ad_event_type,
    TriggerAdEventCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(
        base::BindOnce(&AdsImpl::TriggerSearchResultAdEvent,
                       weak_factory_.GetWeakPtr(), std::move(mojom_creative_ad),
                       mojom_ad_event_type, std::move(callback)));
  }

  GetAdHandler().TriggerSearchResultAdEvent(
      std::move(mojom_creative_ad), mojom_ad_event_type, std::move(callback));
}

void AdsImpl::PurgeOrphanedAdEventsForType(
    mojom::AdType mojom_ad_type,
    PurgeOrphanedAdEventsForTypeCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(
        &AdsImpl::PurgeOrphanedAdEventsForType, weak_factory_.GetWeakPtr(),
        mojom_ad_type, std::move(callback)));
  }

  PurgeOrphanedAdEvents(
      mojom_ad_type,
      base::BindOnce(
          [](mojom::AdType mojom_ad_type,
             PurgeOrphanedAdEventsForTypeCallback callback, bool success) {
            if (!success) {
              BLOG(0,
                   "Failed to purge orphaned ad events for " << mojom_ad_type);
            } else {
              BLOG(1, "Purged orphaned ad events for " << mojom_ad_type);
            }

            std::move(callback).Run(success);
          },
          mojom_ad_type, std::move(callback)));
}

void AdsImpl::GetAdHistory(base::Time from_time,
                           base::Time to_time,
                           GetAdHistoryForUICallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(&AdsImpl::GetAdHistory,
                                          weak_factory_.GetWeakPtr(), from_time,
                                          to_time, std::move(callback)));
  }

  AdHistoryManager::GetForUI(from_time, to_time, std::move(callback));
}

void AdsImpl::ToggleLikeAd(mojom::ReactionInfoPtr mojom_reaction,
                           ToggleReactionCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(
        base::BindOnce(&AdsImpl::ToggleLikeAd, weak_factory_.GetWeakPtr(),
                       std::move(mojom_reaction), std::move(callback)));
  }

  GetReactions().ToggleLikeAd(std::move(mojom_reaction), std::move(callback));
}

void AdsImpl::ToggleDislikeAd(mojom::ReactionInfoPtr mojom_reaction,
                              ToggleReactionCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(
        base::BindOnce(&AdsImpl::ToggleDislikeAd, weak_factory_.GetWeakPtr(),
                       std::move(mojom_reaction), std::move(callback)));
  }

  GetReactions().ToggleDislikeAd(std::move(mojom_reaction),
                                 std::move(callback));
}

void AdsImpl::ToggleLikeSegment(mojom::ReactionInfoPtr mojom_reaction,
                                ToggleReactionCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(
        base::BindOnce(&AdsImpl::ToggleLikeSegment, weak_factory_.GetWeakPtr(),
                       std::move(mojom_reaction), std::move(callback)));
  }

  GetReactions().ToggleLikeSegment(std::move(mojom_reaction),
                                   std::move(callback));
}

void AdsImpl::ToggleDislikeSegment(mojom::ReactionInfoPtr mojom_reaction,
                                   ToggleReactionCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(
        &AdsImpl::ToggleDislikeSegment, weak_factory_.GetWeakPtr(),
        std::move(mojom_reaction), std::move(callback)));
  }

  GetReactions().ToggleDislikeSegment(std::move(mojom_reaction),
                                      std::move(callback));
}

void AdsImpl::ToggleSaveAd(mojom::ReactionInfoPtr mojom_reaction,
                           ToggleReactionCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(
        base::BindOnce(&AdsImpl::ToggleSaveAd, weak_factory_.GetWeakPtr(),
                       std::move(mojom_reaction), std::move(callback)));
  }

  GetReactions().ToggleSaveAd(std::move(mojom_reaction), std::move(callback));
}

void AdsImpl::ToggleMarkAdAsInappropriate(mojom::ReactionInfoPtr mojom_reaction,
                                          ToggleReactionCallback callback) {
  if (task_queue_.should_queue()) {
    return task_queue_.Add(base::BindOnce(
        &AdsImpl::ToggleMarkAdAsInappropriate, weak_factory_.GetWeakPtr(),
        std::move(mojom_reaction), std::move(callback)));
  }

  GetReactions().ToggleMarkAdAsInappropriate(std::move(mojom_reaction),
                                             std::move(callback));
}

///////////////////////////////////////////////////////////////////////////////

void AdsImpl::CreateOrOpenDatabase(mojom::WalletInfoPtr mojom_wallet,
                                   InitializeCallback callback) {
  DatabaseManager::GetInstance().CreateOrOpen(base::BindOnce(
      &AdsImpl::CreateOrOpenDatabaseCallback, weak_factory_.GetWeakPtr(),
      std::move(mojom_wallet), std::move(callback)));
}

void AdsImpl::CreateOrOpenDatabaseCallback(mojom::WalletInfoPtr mojom_wallet,
                                           InitializeCallback callback,
                                           bool success) {
  if (!success) {
    BLOG(0, "Failed to create or open database");
    return FailedToInitialize(std::move(callback));
  }

  MigrateState(base::BindOnce(&AdsImpl::MigrateStateCallback,
                              weak_factory_.GetWeakPtr(),
                              std::move(mojom_wallet), std::move(callback)));
}

void AdsImpl::MigrateStateCallback(mojom::WalletInfoPtr mojom_wallet,
                                   InitializeCallback callback,
                                   bool success) {
  if (!success) {
    return FailedToInitialize(std::move(callback));
  }

  MigrateClientState(base::BindOnce(
      &AdsImpl::MigrateClientStateCallback, weak_factory_.GetWeakPtr(),
      std::move(mojom_wallet), std::move(callback)));
}

void AdsImpl::FailedToInitialize(InitializeCallback callback) {
  TRACE_EVENT_NESTABLE_ASYNC_END1(kTraceEventCategory, "AdsImpl::Initialize",
                                  TRACE_ID_LOCAL(this), "success", false);

  BLOG(0, "Failed to initialize ads");

  std::move(callback).Run(/*success=*/false);
}

void AdsImpl::SuccessfullyInitialized(mojom::WalletInfoPtr mojom_wallet,
                                      InitializeCallback callback) {
  TRACE_EVENT_NESTABLE_ASYNC_END1(kTraceEventCategory, "AdsImpl::Initialize",
                                  TRACE_ID_LOCAL(this), "success", true);

  BLOG(1, "Successfully initialized ads");

  is_initialized_ = true;

  if (mojom_wallet) {
    GetAccount().SetWallet(mojom_wallet->payment_id,
                           mojom_wallet->recovery_seed_base64);
  }

  GetAdsClient().NotifyPendingObservers();

  // Flush any queued tasks that occurred during initialization.
  task_queue_.FlushAndStopQueueing();

  std::move(callback).Run(/*success=*/true);
}

void AdsImpl::MigrateClientStateCallback(mojom::WalletInfoPtr mojom_wallet,
                                         InitializeCallback callback,
                                         bool success) {
  if (!success) {
    return FailedToInitialize(std::move(callback));
  }

  ClientStateManager::GetInstance().LoadState(base::BindOnce(
      &AdsImpl::LoadClientStateCallback, weak_factory_.GetWeakPtr(),
      std::move(mojom_wallet), std::move(callback)));
}

void AdsImpl::LoadClientStateCallback(mojom::WalletInfoPtr mojom_wallet,
                                      InitializeCallback callback,
                                      bool success) {
  if (!success) {
    return FailedToInitialize(std::move(callback));
  }

  MigrateConfirmationState(base::BindOnce(
      &AdsImpl::MigrateConfirmationStateCallback, weak_factory_.GetWeakPtr(),
      std::move(mojom_wallet), std::move(callback)));
}

void AdsImpl::MigrateConfirmationStateCallback(
    mojom::WalletInfoPtr mojom_wallet,
    InitializeCallback callback,
    bool success) {
  if (!success) {
    return FailedToInitialize(std::move(callback));
  }

  std::optional<WalletInfo> wallet;
  if (mojom_wallet) {
    wallet = CreateWalletFromRecoverySeed(&*mojom_wallet);
    if (!wallet) {
      BLOG(0, "Invalid wallet");
      return FailedToInitialize(std::move(callback));
    }
  }

  ConfirmationStateManager::GetInstance().LoadState(
      wallet, base::BindOnce(&AdsImpl::LoadConfirmationStateCallback,
                             weak_factory_.GetWeakPtr(),
                             std::move(mojom_wallet), std::move(callback)));
}

void AdsImpl::LoadConfirmationStateCallback(mojom::WalletInfoPtr mojom_wallet,
                                            InitializeCallback callback,
                                            bool success) {
  if (!success) {
    BLOG(0, "Failed to load confirmation state");
    return FailedToInitialize(std::move(callback));
  }

  SuccessfullyInitialized(std::move(mojom_wallet), std::move(callback));
}

}  // namespace brave_ads
