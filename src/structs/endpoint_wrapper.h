#pragma once

struct EndpointWrapper {
    const char *host;
    const uint16_t port;

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

extern "C" EXPORT inline void FreeEndpointWrapper(const EndpointWrapper *wrapper) {
    delete[] wrapper->host;
    delete wrapper;
}