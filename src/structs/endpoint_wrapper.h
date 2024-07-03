#pragma once

#include <cstdint>
#include <clickhouse/client.h>

#include <export.h>

using namespace clickhouse;

struct chc_endpoint {
    const char *host;
    uint16_t port;

    chc_endpoint() : host(nullptr),
                        port(9000) {
    };

    [[nodiscard]] Endpoint toEndpoint() const {
        Endpoint endpoint;
        endpoint.host = host == nullptr ? std::string() : std::string(host);
        endpoint.port = port;

        return endpoint;
    }
};

extern "C" EXPORT inline void chc_endpoint_free(chc_endpoint *wrapper) {
    delete[] wrapper->host;
    wrapper->host = nullptr;
}
