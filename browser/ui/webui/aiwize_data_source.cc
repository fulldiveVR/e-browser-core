#include "brave/browser/ui/webui/aiwize_data_source.h"

#include "base/files/file_path.h"
#include "base/functional/bind.h"
#include "base/memory/ref_counted_memory.h"
#include "base/strings/string_util.h"
#include "base/task/single_thread_task_runner.h"
#include "base/task/task_traits.h"
#include "base/task/thread_pool.h"
#include "base/time/time.h"
#include "chrome/common/webui_url_constants.h"
#include "net/base/mime_util.h"
#include "net/url_request/url_request.h"
#include "services/network/public/cpp/resource_request.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"
#include "services/network/public/cpp/simple_url_loader.h"
#include "services/network/public/mojom/content_security_policy.mojom.h"
#include "services/network/public/mojom/url_response_head.mojom.h"

namespace aiwize {

namespace {

constexpr int64_t kMaxDownloadBytes = 10 * 1024 * 1024;
static constexpr int kTryDelaySeconds = 1;

constexpr net::NetworkTrafficAnnotationTag kTrafficAnnotation =
    net::DefineNetworkTrafficAnnotation("aiwize_home", R"(
      semantics {
        sender: "AIWizeHome"
        description:
          "Fetches data for internal web-site"
        trigger:
          "When web site request internal data"
        data: "URL of the data to be fetched."
        destination: WEBSITE
      }
      policy {
        cookies_allowed: NO
        setting:
          "None"
      }
    )");
}  // namespace

AIWizeDataSource::AIWizeDataSource(
    scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory)
    : url_loader_factory_(url_loader_factory) {}

AIWizeDataSource::~AIWizeDataSource() = default;

std::string AIWizeDataSource::GetSource() {
  return "home";
}

void AIWizeDataSource::StartDataRequest(
    const GURL& url,
    const content::WebContents::Getter& wc_getter,
    content::URLDataSource::GotDataCallback callback) {
  if (!url.is_valid()) {
    std::move(callback).Run(nullptr);
    return;
  }

  GURL::Replacements replacements;
  replacements.SetSchemeStr(url::kHttpScheme);
  replacements.SetHostStr("127.0.0.1");
  replacements.SetPortStr("22003");
  const GURL fixed_url = url.ReplaceComponents(replacements);
  RequestData(fixed_url, std::move(callback), 0);
}

void AIWizeDataSource::RequestData(
    const GURL& url,
    content::URLDataSource::GotDataCallback callback,
    int retry_count) {
  auto request = std::make_unique<network::ResourceRequest>();
  request->url = url;
  request->load_flags = net::LOAD_DO_NOT_SAVE_COOKIES;
  request->method = net::HttpRequestHeaders::kGetMethod;
  request->referrer_policy = net::ReferrerPolicy::NO_REFERRER;
  request->credentials_mode = network::mojom::CredentialsMode::kOmit;

  auto url_loader =
      network::SimpleURLLoader::Create(std::move(request), kTrafficAnnotation);

  url_loader->SetAllowHttpErrorResults(true);

  auto* url_loader_ptr = url_loader.get();

  auto download_callback = base::BindOnce(
      &AIWizeDataSource::OnURLResponse, weak_factory_.GetWeakPtr(),
      std::move(callback), std::move(url_loader), retry_count);

  url_loader_ptr->DownloadToString(url_loader_factory_.get(),
                                   std::move(download_callback),
                                   kMaxDownloadBytes);
}

void AIWizeDataSource::OnURLResponse(
    content::URLDataSource::GotDataCallback callback,
    std::unique_ptr<network::SimpleURLLoader> loader,
    int retry_count,
    std::unique_ptr<std::string> response_body) {
  auto response_code = -1;
  if (loader->ResponseInfo()) {
    auto headers_list = loader->ResponseInfo()->headers;
    if (headers_list) {
      response_code = headers_list->response_code();
    }
  }

  if (response_code == -1 && retry_count < 50) {
    base::OnceClosure task = base::BindOnce(
        &AIWizeDataSource::RetryRequest, weak_factory_.GetWeakPtr(),
        std::move(loader->GetFinalURL()), std::move(callback), retry_count + 1);

    base::SequencedTaskRunner::GetCurrentDefault()->PostDelayedTask(
        FROM_HERE, std::move(task), base::Seconds(kTryDelaySeconds));
    return;
  }

  bool is_ok =
      loader->NetError() == net::OK && response_body && response_code == 200;

  std::string patch_content = is_ok ? *response_body : "";

  if (patch_content != "") {
    std::move(callback).Run(
        base::MakeRefCounted<base::RefCountedString>(std::move(patch_content)));
  } else {
    std::move(callback).Run(nullptr);
  }
}

void AIWizeDataSource::RetryRequest(
    const GURL& url,
    content::URLDataSource::GotDataCallback callback,
    int retry_count) {
  RequestData(std::move(url), std::move(callback), retry_count);
}

std::string AIWizeDataSource::GetMimeType(const GURL& url) {
  const std::string path = content::URLDataSource::URLToRequestPath(url);

  std::string file_path = path.substr(0, path.find_first_of('?'));

  if (base::EndsWith(file_path, ".css", base::CompareCase::INSENSITIVE_ASCII)) {
    return "text/css";
  }

  if (base::EndsWith(file_path, ".js", base::CompareCase::INSENSITIVE_ASCII)) {
    return "application/javascript";
  }

  if (base::EndsWith(file_path, ".json",
                     base::CompareCase::INSENSITIVE_ASCII)) {
    return "application/json";
  }

  if (base::EndsWith(file_path, ".pdf", base::CompareCase::INSENSITIVE_ASCII)) {
    return "application/pdf";
  }

  if (base::EndsWith(file_path, ".svg", base::CompareCase::INSENSITIVE_ASCII)) {
    return "image/svg+xml";
  }

  if (base::EndsWith(file_path, ".jpg", base::CompareCase::INSENSITIVE_ASCII)) {
    return "image/jpeg";
  }

  if (base::EndsWith(file_path, ".png", base::CompareCase::INSENSITIVE_ASCII)) {
    return "image/png";
  }

  return "text/html";
}

bool AIWizeDataSource::ShouldServiceRequest(
    const GURL& url,
    content::BrowserContext* browser_context,
    int render_process_id) {
  if (url.SchemeIs(content::kChromeUIScheme) ||
      url.SchemeIs(content::kBraveUIScheme)) {
    return true;
  }
  return URLDataSource::ShouldServiceRequest(url, browser_context,
                                             render_process_id);
}

std::string AIWizeDataSource::GetAccessControlAllowOriginForOrigin(
    const std::string& origin) {
  // For now we give access for all "chrome://*" origins.
  std::string allowed_origin_prefix = "chrome://";
  if (!base::StartsWith(origin, allowed_origin_prefix,
                        base::CompareCase::SENSITIVE)) {
    return "";
  }
  return origin;
}

}  // namespace aiwize
