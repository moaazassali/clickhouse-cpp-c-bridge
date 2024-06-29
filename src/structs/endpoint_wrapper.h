#pragma once

#include <cstdint>
#include <clickhouse/client.h>

#include <export.h>

using namespace clickhouse;

struct EndpointWrapper {
    const char *host;
    uint16_t port;

    EndpointWrapper() : host(nullptr),
                        port(9000) {
    };

    [[nodiscard]] Endpoint toEndpoint() const {
        Endpoint endpoint;
        endpoint.host = host == nullptr ? std::string() : std::string(host);
        endpoint.port = port;

        return endpoint;
    }
};

extern "C" EXPORT inline void FreeEndpointWrapper(EndpointWrapper *wrapper) {
    delete[] wrapper->host;
    wrapper->host = nullptr;
}
