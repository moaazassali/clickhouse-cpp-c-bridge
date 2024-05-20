#pragma once

#include <clickhouse/client.h>
#include "structs/clickhouse_result_status.h"
#include "structs/server_info_wrapper.h"
#include "export.h"
#include "structs/client_options_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline Client *CreateClient(const ClientOptionsWrapper *optionsWrapper) {
    return new Client(optionsWrapper->toClientOptions());
}

extern "C" EXPORT inline void FreeClient(const Client *client) {
    delete client;
}

extern "C" EXPORT inline ClickHouseResultStatus Execute(Client *client, const Query *query) {
    return TryCatchClickHouseError([&]() {
        client->Execute(*query);
    });
}

extern "C" EXPORT inline ClickHouseResultStatus Select(Client *client, const char *query,
                                                       SelectCallback cb) {
    return TryCatchClickHouseError([&]() {
        client->Select(query, cb);
    });
}

extern "C" EXPORT inline ClickHouseResultStatus SelectWithQueryId(
    Client *client, const char *query, const char *query_id, SelectCallback cb) {
    return TryCatchClickHouseError([&]() {
        client->Select(query, query_id, cb);
    });
}

extern "C" EXPORT inline ClickHouseResultStatus SelectCancelable(
    Client *client, const char *query, SelectCancelableCallback cb) {
    return TryCatchClickHouseError([&]() {
        client->SelectCancelable(query, cb);
    });
}

extern "C" EXPORT inline ClickHouseResultStatus SelectCancelableWithQueryId(
    Client *client, const char *query, const char *query_id, SelectCancelableCallback cb) {
    return TryCatchClickHouseError([&]() {
        client->SelectCancelable(query, query_id, cb);
    });
}

extern "C" EXPORT inline ClickHouseResultStatus Insert(Client *client, const char *table_name,
                                                       const Block *block) {
    return TryCatchClickHouseError([&]() {
        client->Insert(table_name, *block);
    });
}

extern "C" EXPORT inline ClickHouseResultStatus InsertWithQueryId(
    Client *client, const char *table_name, const char *query_id, const Block *block) {
    return TryCatchClickHouseError([&]() {
        client->Insert(table_name, query_id, *block);
    });
}

extern "C" EXPORT inline ClickHouseResultStatus Ping(Client *client) {
    return TryCatchClickHouseError([&]() {
        client->Ping();
    });
}

extern "C" EXPORT inline ClickHouseResultStatus ResetConnection(Client *client) {
    return TryCatchClickHouseError([&]() {
        client->ResetConnection();
    });
}

extern "C" EXPORT inline ServerInfoWrapper GetServerInfo(const Client *client) {
    if (client == nullptr) {
        constexpr ServerInfoWrapper wrapper{
            nullptr,
            nullptr,
            nullptr,
            0,
            0,
            0,
            0
        };
        return wrapper;
    }

    const auto serverInfo = client->GetServerInfo();

    // Allocate memory and copy string contents
    const size_t nameLen = serverInfo.name.length();
    const auto name = new char[nameLen + 1];
    std::strcpy(name, serverInfo.name.c_str());

    const size_t timezoneLen = serverInfo.timezone.length();
    const auto timezone = new char[timezoneLen + 1];
    std::strcpy(timezone, serverInfo.timezone.c_str());

    const size_t displayNameLen = serverInfo.display_name.length();
    const auto display_name = new char[displayNameLen + 1];
    std::strcpy(display_name, serverInfo.display_name.c_str());

    const ServerInfoWrapper wrapper{
        name,
        timezone,
        display_name,
        serverInfo.version_major,
        serverInfo.version_minor,
        serverInfo.version_patch,
        serverInfo.revision
    };

    return wrapper;
}

extern "C" EXPORT inline EndpointWrapper GetCurrentEndpoint(const Client *client) {
    auto endpointWrapper = EndpointWrapper();
    if (const auto &optionalEndpoint = client->GetCurrentEndpoint(); optionalEndpoint.has_value()) {
        endpointWrapper.port = optionalEndpoint.value().port;

        const size_t displayNameLen = optionalEndpoint.value().host.length();
        const auto display_name = new char[displayNameLen + 1];
        std::strcpy(display_name, optionalEndpoint.value().host.c_str());

        endpointWrapper.host = display_name;
    } else {
        endpointWrapper.port = 0;
        endpointWrapper.host = "";
    }

    return endpointWrapper;
}

extern "C" EXPORT inline ClickHouseResultStatus ResetConnectionEndpoint(Client *client) {
    return TryCatchClickHouseError([&]() {
        client->ResetConnectionEndpoint();
    });
}

extern "C" EXPORT inline Client::Version GetVersion(const Client *client) {
    return client->GetVersion();
}
