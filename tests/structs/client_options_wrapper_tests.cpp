#include <doctest/doctest.h>

#include "structs/client_options_wrapper.h"

TEST_CASE("Compression method is set correctly") {
    chc_client_options optionsWrapper{};
    optionsWrapper.compression_method = 1;

    CHECK(optionsWrapper.getCompressionMethodEnum() == CompressionMethod::LZ4);

    optionsWrapper.compression_method = 2;
    CHECK(optionsWrapper.getCompressionMethodEnum() == CompressionMethod::ZSTD);

    optionsWrapper.compression_method = -1;
    CHECK(optionsWrapper.getCompressionMethodEnum() == CompressionMethod::None);

    optionsWrapper.compression_method = 0;
    CHECK(optionsWrapper.getCompressionMethodEnum() == CompressionMethod::None);

    optionsWrapper.compression_method = 3;
    CHECK(optionsWrapper.getCompressionMethodEnum() == CompressionMethod::None);
}

TEST_CASE("Correctly create client options") {
    // dynamically allocate memory for string
    const char *host = new char[10];
    std::strcpy(const_cast<char *>(host), "localhost");
    constexpr auto port = 8000;
    chc_client_options optionsWrapper{};
    optionsWrapper.host = host;
    optionsWrapper.port = port;

    ClientOptions options = optionsWrapper.toClientOptions();
    CHECK(std::string(options.host) == std::string(host));
    CHECK(options.port == port);
}

TEST_CASE("Adding endpoints to client options correctly") {
    chc_client_options optionsWrapper{};
    chc_endpoint endpointWrapper1{};
    endpointWrapper1.host = "localhost";
    endpointWrapper1.port = 8000;
    chc_endpoint endpointWrapper2{};
    endpointWrapper2.host = "localhost";
    endpointWrapper2.port = 8001;
    optionsWrapper.endpoints = new chc_endpoint[2]{endpointWrapper1, endpointWrapper2};
    optionsWrapper.endpoints_count = 2;

    ClientOptions options = optionsWrapper.toClientOptions();
    CHECK(options.endpoints.size() == 2);
    CHECK(options.endpoints[0].host == "localhost");
    CHECK(options.endpoints[0].port == 8000);
    CHECK(options.endpoints[1].host == "localhost");
    CHECK(options.endpoints[1].port == 8001);
}
