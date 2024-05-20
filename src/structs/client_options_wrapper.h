#pragma once

struct ClientOptionsWrapper {
    const char *host;
    const uint16_t port;
    // endpoints
    const char *default_database;
    const char *user;
    const char *password;
    const bool rethrow_exceptions;
    const bool ping_before_query;
    const uint32_t send_retries;
    // retry_timeout
    const int32_t compression;
    const bool tcp_keepalive;
    // tcp_keepalive_idle
    // tcp_keepalive_intvl
    const uint32_t tcp_keepalive_cnt;
    const bool tcp_nodelay;
    // connection_connect_timeout
    // connection_recv_timeout
    // connection_send_timeout
    const bool backward_compatibility_lowcardinality_as_wrapped_column;
    const uint32_t max_compression_chunk_size;

    ClientOptionsWrapper() : host(""),
                             port(9000),
                             default_database("default"),
                             user("default"),
                             password(""),
                             rethrow_exceptions(true),
                             ping_before_query(false),
                             send_retries(1),
                             compression(-1),
                             tcp_keepalive(false),
                             tcp_keepalive_cnt(3),
                             tcp_nodelay(true),
                             backward_compatibility_lowcardinality_as_wrapped_column(false),
                             max_compression_chunk_size(65535){
    };
};
