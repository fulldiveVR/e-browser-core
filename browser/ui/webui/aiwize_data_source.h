#ifndef BRAVE_BROWSER_UI_WEBUI_AIWIZE_DATA_SOURCE_H_
#define BRAVE_BROWSER_UI_WEBUI_AIWIZE_DATA_SOURCE_H_

#include <optional>
#include <string>

#include "base/memory/scoped_refptr.h"
#include "base/memory/weak_ptr.h"
#include "content/public/browser/url_data_source.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"
#include "services/network/public/cpp/simple_url_loader.h"

namespace aiwize {

class AIWizeDataSource : public content::URLDataSource {
 public:
  AIWizeDataSource(
      scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory);
  ~AIWizeDataSource() override;

  // content::URLDataSource implementation.
  std::string GetSource() override;
  void StartDataRequest(
      const GURL& url,
      const content::WebContents::Getter& wc_getter,
      content::URLDataSource::GotDataCallback callback) override;
  std::string GetMimeType(const GURL& url) override;
  bool ShouldServiceRequest(const GURL& url,
                            content::BrowserContext* browser_context,
                            int render_process_id) override;
  std::string GetAccessControlAllowOriginForOrigin(
      const std::string& origin) override;

  void OnURLResponse(content::URLDataSource::GotDataCallback callback,
                     std::unique_ptr<network::SimpleURLLoader> loader,
                     int retry_count,
                     std::unique_ptr<std::string> response_body);

  void RetryRequest(const GURL& url,
                    content::URLDataSource::GotDataCallback callback,
                    int retry_count);

 private:
  void RequestData(const GURL& url,
                   content::URLDataSource::GotDataCallback callback,
                   int retry_count);

 private:
  scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory_;
  base::WeakPtrFactory<AIWizeDataSource> weak_factory_{this};
};

}  // namespace aiwize

#endif  // BRAVE_BROWSER_UI_WEBUI_AIWIZE_DATA_SOURCE_H_
