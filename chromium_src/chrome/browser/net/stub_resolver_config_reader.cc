#include "chrome/browser/net/stub_resolver_config_reader.h"

#include "chrome/browser/net/secure_dns_config.h"
#include "net/dns/public/dns_over_https_config.h"
#include "services/network/public/mojom/network_service.mojom.h"

namespace {
inline constexpr char kDnsConfig[] =
    "https://doh.cleanbrowsing.org/doh/family-filter{?dns}";
}  // namespace

#define SecureDnsConfig(SECURE_DNS_MODE, SECURE_DOH_CONFIG,           \
                        FORCED_MANAGEMENT_MODE)                       \
  SecureDnsConfig(net::SecureDnsMode::kSecure,                        \
                  net::DnsOverHttpsConfig::FromStringLax(kDnsConfig), \
                  SecureDnsConfig::ManagementMode::kDisabledManaged)

#define ConfigureStubHostResolver(                                           \
    INSECURE_DNS_CLIENT_ENABLED, HAPPY_EYEBALLS_V3_ENABLED, SECURE_DNS_MODE, \
    DNS_OVER_HTTPS_CONFIG, ADDITIONAL_DNS_TYPES_ENABLED)                     \
  ConfigureStubHostResolver(                                                 \
      true, HAPPY_EYEBALLS_V3_ENABLED, net::SecureDnsMode::kSecure,          \
      net::DnsOverHttpsConfig::FromStringLax(kDnsConfig),                    \
      ADDITIONAL_DNS_TYPES_ENABLED)

#include <chrome/browser/net/stub_resolver_config_reader.cc>

#undef ConfigureStubHostResolver
#undef SecureDnsConfig
