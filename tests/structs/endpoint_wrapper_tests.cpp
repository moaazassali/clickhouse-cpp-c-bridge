#include <doctest/doctest.h>

#include "structs/endpoint_wrapper.h"

TEST_CASE("Correctly create and free endpoint") {
    // dynamically allocate memory for string
    const char *host = new char[10];
    std::strcpy(const_cast<char *>(host), "localhost");
    constexpr auto port = 9000;
    chc_endpoint endpointWrapper{};
    endpointWrapper.host = host;
    endpointWrapper.port = port;

    Endpoint endpoint = endpointWrapper.toEndpoint();
    CHECK(std::string(endpoint.host) == std::string(host));
    CHECK(endpoint.port == port);

    chc_endpoint_free(&endpointWrapper);
    CHECK(endpointWrapper.host == nullptr);
}
