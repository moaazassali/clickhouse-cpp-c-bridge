#pragma once

#include "endpoint_wrapper.h"

struct ClientOptionsWrapper {
    const char *host;
    const uint16_t port;
    const EndpointWrapper *endpoints;
    size_t endpoints_count;
    const char *default_database;
    const char *user;
    const char *password;
    const bool rethrow_exceptions;
    const bool ping_before_query;
    const uint32_t send_retries;
    const int64_t retry_timeout;
    const int32_t compression_method;
    const bool tcp_keepalive;
    const int64_t tcp_keepalive_idle;
    const int64_t tcp_keepalive_intvl;
    const uint32_t tcp_keepalive_cnt;
    const bool tcp_nodelay;
    const int64_t connection_connect_timeout;
    const int64_t connection_recv_timeout;
    const int64_t connection_send_timeout;
    const bool backward_compatibility_lowcardinality_as_wrapped_column;
    const uint32_t max_compression_chunk_size;

    ClientOptionsWrapper() : host(nullptr),
                             port(9000),
                             endpoints(nullptr),
                             endpoints_count(0),
                             default_database("default"),
                             user("default"),
                             password(nullptr),
                             rethrow_exceptions(true),
                             ping_before_query(false),
                             send_retries(1),
                             retry_timeout(5),
                             compression_method(-1),
                             tcp_keepalive(false),
                             tcp_keepalive_idle(60),
                             tcp_keepalive_intvl(5),
                             tcp_keepalive_cnt(3),
                             tcp_nodelay(true),
                             connection_connect_timeout(5),
                             connection_recv_timeout(0),
                             connection_send_timeout(0),
                             backward_compatibility_lowcardinality_as_wrapped_column(false),
                             max_compression_chunk_size(65535) {
    };

    // method to conver to ClientOptions
    [[nodiscard]] ClientOptions toClientOptions() const {
        ClientOptions options;
        options.host = host == nullptr ? std::string() : std::string(host);
        options.port = port;

        options.endpoints = std::vector<Endpoint>();
        for (auto i = 0; i < endpoints_count; i++) {
            options.endpoints.push_back(endpoints[i].toEndpoint());
        }

        options.default_database = default_database == nullptr ? std::string() : std::string(default_database);
        options.user = user == nullptr ? std::string() : std::string(user);
        options.password = password == nullptr ? std::string() : std::string(password);
        options.rethrow_exceptions = rethrow_exceptions;
        options.ping_before_query = ping_before_query;
        options.send_retries = send_retries;
        options.retry_timeout = std::chrono::seconds(retry_timeout);
        options.compression_method = getCompressionMethodEnum();
        options.tcp_keepalive = tcp_keepalive;
        options.tcp_keepalive_idle = std::chrono::seconds(tcp_keepalive_idle);
        options.tcp_keepalive_intvl = std::chrono::seconds(tcp_keepalive_intvl);
        options.tcp_keepalive_cnt = tcp_keepalive_cnt;
        options.tcp_nodelay = tcp_nodelay;
        options.connection_connect_timeout = std::chrono::seconds(connection_connect_timeout);
        options.connection_recv_timeout = std::chrono::milliseconds(connection_recv_timeout);
        options.connection_send_timeout = std::chrono::milliseconds(connection_send_timeout);
        options.backward_compatibility_lowcardinality_as_wrapped_column =
                backward_compatibility_lowcardinality_as_wrapped_column;
        options.max_compression_chunk_size = max_compression_chunk_size;

        return options;
    }

    [[nodiscard]] CompressionMethod getCompressionMethodEnum() const {
        switch (compression_method) {
            case -1:
                return CompressionMethod::None;
            case 1:
                return CompressionMethod::LZ4;
            default:
                return CompressionMethod::None;
        }
    }
};

extern "C" EXPORT inline void FreeClientOptions(ClientOptionsWrapper *options) {
    delete[] options->host;
    delete[] options->endpoints;
    delete[] options->default_database;
    delete[] options->user;
    delete[] options->password;

    options->host = nullptr;
    options->endpoints = nullptr;
    options->endpoints_count = 0;
    options->default_database = nullptr;
    options->user = nullptr;
    options->password = nullptr;
}
