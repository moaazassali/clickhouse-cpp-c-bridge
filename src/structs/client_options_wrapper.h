#pragma once

#include <chrono>
#include <cstdint>
#include <vector>
#include <clickhouse/client.h>

#include <structs/endpoint_wrapper.h>

using namespace clickhouse;

struct chc_client_options {
    const char *host;
    uint16_t port;
    const chc_endpoint *endpoints;
    size_t endpoints_count;
    const char *default_database;
    const char *user;
    const char *password;
    bool rethrow_exceptions;
    bool ping_before_query;
    uint32_t send_retries;
    int64_t retry_timeout;
    int32_t compression_method;
    bool tcp_keepalive;
    int64_t tcp_keepalive_idle;
    int64_t tcp_keepalive_intvl;
    uint32_t tcp_keepalive_cnt;
    bool tcp_nodelay;
    int64_t connection_connect_timeout;
    int64_t connection_recv_timeout;
    int64_t connection_send_timeout;
    bool backward_compatibility_lowcardinality_as_wrapped_column;
    uint32_t max_compression_chunk_size;

    chc_client_options() : host(""),
                             port(9000),
                             endpoints(nullptr),
                             endpoints_count(0),
                             default_database("default"),
                             user("default"),
                             password(""),
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

    // method to convert to ClientOptions
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
            case 2:
                return CompressionMethod::ZSTD;
            default:
                return CompressionMethod::None;
        }
    }
};
