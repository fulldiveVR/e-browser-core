/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/ai_chat/core/browser/engine/remote_completion_openai_client.h"

#include <base/containers/flat_map.h>

#include <optional>
#include <string_view>
#include <utility>

#include "base/containers/flat_set.h"
#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "base/json/json_reader.h"
#include "base/json/json_writer.h"
#include "base/json/string_escape.h"
#include "base/no_destructor.h"
#include "base/strings/strcat.h"
#include "base/values.h"
#include "brave/brave_domains/service_domains.h"
#include "brave/components/ai_chat/core/browser/constants.h"
#include "brave/components/ai_chat/core/common/buildflags/buildflags.h"
#include "brave/components/ai_chat/core/common/features.h"
#include "brave/components/constants/brave_services_key.h"
#include "net/http/http_status_code.h"
#include "net/traffic_annotation/network_traffic_annotation.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"
#include "services/network/public/cpp/simple_url_loader.h"
#include "url/gurl.h"

namespace ai_chat {
namespace {

constexpr char kAIChatCompletionPath[] = "v1/chat/completions";

std::string CreateApiParametersDict(
    const std::string& prompt,
    const std::string& model_name,
    const base::flat_set<std::string_view>& stop_sequences,
    const std::vector<std::string> additional_stop_sequences,
    const bool is_sse_enabled) {
  base::Value::List all_stop_sequences;
  for (auto& item : additional_stop_sequences) {
    all_stop_sequences.Append(item);
  }
  for (auto& item : stop_sequences) {
    all_stop_sequences.Append(item);
  }

  DCHECK(!model_name.empty());

  // const double temp = ai_chat::features::kAITemperature.Get();
  //  dict.Set("stop", std::move(all_stop_sequences));

  std::string stream = "false";
  if (is_sse_enabled) {
    stream = "true";
  }

  std::string message =
      "{ \"model\": \"" + model_name +
      "\", \"messages\": [{ \"role\": \"user\", \"content\": " +
      base::GetQuotedJSONString(prompt) + "}], \"stream\":" + stream + "}";

  DVLOG(1) << __func__ << " Prompt: |" << prompt << "|\n";
  DVLOG(1) << __func__ << " Using model: " << model_name;

  return message;
}

std::string FetchMessageFromJson(const std::string& json_string) {
  std::string summary_string_trimmed;
  base::TrimWhitespaceASCII(json_string, base::TrimPositions::TRIM_ALL,
                            &summary_string_trimmed);

  if (summary_string_trimmed.empty()) {
    return "";
  }

  std::optional<base::Value> records_v = base::JSONReader::Read(
      json_string, base::JSONParserOptions::JSON_PARSE_RFC);

  if (!records_v || !records_v->is_dict()) {
    return "";
  }

  const auto& records_dict = records_v->GetDict();
  if (records_dict.empty()) {
    return "";
  }

  const base::Value::List* choices_list = records_dict.FindList("choices");
  if (choices_list->empty()) {
    return "";
  }

  const base::Value& first_item = (*choices_list)[0];

  if (!first_item.is_dict()) {
    return "";
  }
  const auto* message = first_item.GetDict().FindDict("message");
  if (!message) {
    return "";
  }
  const auto* content = message->FindString("content");
  if (!content || content->empty()) {
    return "";
  }

  return *content;
}
std::string FetchMessageFromDict(const base::Value::Dict& dict) {
  if (dict.empty()) {
    return "";
  }

  const base::Value::List* choices_list = dict.FindList("choices");
  if (choices_list->empty()) {
    return "";
  }
  const base::Value& first_item = (*choices_list)[0];

  if (!first_item.is_dict()) {
    return "";
  }
  const base::Value::Dict* delta_dict = first_item.GetDict().FindDict("delta");
  if (delta_dict->empty()) {
    return "";
    // return first_item.GetDict().DebugString();
  }
  const auto* content = delta_dict->FindString("content");
  if (!content || content->empty()) {
    return "";
  }

  return *content;
}

GURL GetEndpointUrl(const std::string& path) {
  DCHECK(!path.starts_with("/"));

  auto* hostname = "api.openai.com";

  GURL url{base::StrCat(
      {url::kHttpsScheme, url::kStandardSchemeSeparator, hostname, "/", path})};

  DCHECK(url.is_valid()) << "Invalid API Url: " << url.spec();

  return url;
}


std::string DecodeParam(const std::string& text) {
  int count = text.length();
  std::string result = std::string(count, '\0');;

  for (int i = 0; i < count; ++i) { 
    result[i] = text[i] + 1;
  }

  return result;
}
}  // namespace

// static

RemoteCompletionOpenAIClient::RemoteCompletionOpenAIClient(
    const std::string& model_name,
    const base::flat_set<std::string_view>& stop_sequences,
    scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory,
    AIChatCredentialManager* credential_manager)
    : RemoteCompletionClient(model_name, stop_sequences, url_loader_factory, credential_manager){}
RemoteCompletionOpenAIClient::~RemoteCompletionOpenAIClient() = default;

void RemoteCompletionOpenAIClient::QueryPrompt(
    const std::string& prompt,
    const std::vector<std::string>& extra_stop_sequences,
    GenerationCompletedCallback data_completed_callback,
    GenerationDataCallback
        data_received_callback /* = base::NullCallback() */) {
  const GURL api_url = GetEndpointUrl(kAIChatCompletionPath);
  base::flat_map<std::string, std::string> headers;

  headers.emplace(DecodeParam("@tsgnqhy`shnm"), DecodeParam("Ad`qdq\x1frj,yjaXvWad7FYxvE5EVgeuS2AkajEIPwVy1wbcYXOaJ4JiyqSo"));
  headers.emplace("Accept", "text/event-stream");

  const bool is_sse_enabled =
      ai_chat::features::kAIChatSSE.Get() && !data_received_callback.is_null();
  // const bool is_sse_enabled =false;

  const std::string dict =
      CreateApiParametersDict(prompt, model_name_, stop_sequences_,
                              std::move(extra_stop_sequences), is_sse_enabled);

  if (is_sse_enabled) {
    VLOG(2) << "Making streaming AI Chat API Request";
    auto on_received = base::BindRepeating(
        &RemoteCompletionOpenAIClient::OnQueryDataReceived,
        weak_ptr_factory_.GetWeakPtr(), std::move(data_received_callback));
    auto on_complete = base::BindOnce(&RemoteCompletionOpenAIClient::OnQueryCompleted,
                                      weak_ptr_factory_.GetWeakPtr(),
                                      std::move(data_completed_callback));

    api_request_helper_.RequestSSE("POST", api_url, dict, "application/json",
                                   std::move(on_received),
                                   std::move(on_complete), headers, {});
  } else {
    VLOG(2) << "Making non-streaming AI Chat API Request";
    auto on_complete = base::BindOnce(&RemoteCompletionOpenAIClient::OnQueryCompleted,
                                      weak_ptr_factory_.GetWeakPtr(),
                                      std::move(data_completed_callback));

    api_request_helper_.Request("POST", api_url, dict, "application/json",
                                std::move(on_complete), headers, {});
  }
}

void RemoteCompletionOpenAIClient::ClearAllQueries() {
  api_request_helper_.CancelAll();
}

void RemoteCompletionOpenAIClient::OnQueryDataReceived(
    EngineConsumer::GenerationDataCallback callback,
    base::expected<base::Value, std::string> result) {
  if (!result.has_value() || !result->is_dict()) {
    return;
  }

  std::string completion = FetchMessageFromDict(result->GetDict());

  // const std::string value = FetchMessageFromDict(result->GetDict());
  // if (!value.empty()) {
  //   completion = base::TrimWhitespaceASCII(value, base::TRIM_ALL);
  // }

  if (!completion.empty()) {
    callback.Run(std::move(completion));
  }
}

void RemoteCompletionOpenAIClient::OnQueryCompleted(
    EngineConsumer::GenerationCompletedCallback callback,
    APIRequestResult result) {
  const bool success = result.Is2XXResponseCode();

  if (success) {
    std::string completion = "";
    std::string body = result.SerializeBodyToString();
    if (!body.empty()) {
      const std::string value = FetchMessageFromJson(body);
      if (!value.empty()) {
        completion = base::TrimWhitespaceASCII(value, base::TRIM_ALL);
      }
    }

    std::move(callback).Run(base::ok(std::move(completion)));
    return;
  }

  // Handle error
  mojom::APIError error;

  if (net::HTTP_TOO_MANY_REQUESTS == result.response_code()) {
    error = mojom::APIError::RateLimitReached;
  } else if (net::HTTP_REQUEST_ENTITY_TOO_LARGE == result.response_code()) {
    error = mojom::APIError::ContextLimitReached;
  } else {
    error = mojom::APIError::ConnectionIssue;
  }

  std::move(callback).Run(base::unexpected(std::move(error)));
  // std::move(callback).Run(base::ok(std::move("error final_url: ") + std::move(result.final_url().spec()) + std::move("          response_code:  ") +  std::to_string(result.response_code()) + std::move("          body:  ") +  std::move(result.body())));  // TODO: XXX
}

}  // namespace ai_chat
