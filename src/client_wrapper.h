#pragma once

#include <clickhouse/client.h>
#include "structs/clickhouse_result_status.h"
#include "structs/server_info_wrapper.h"

using namespace clickhouse;

extern "C" __declspec(dllexport) inline Client *CreateClient(const char *host) {
    return new Client(ClientOptions().SetHost(host));
}

extern "C" __declspec(dllexport) inline void FreeClient(const Client *client) {
    delete client;
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus Execute(Client *client, const Query *query) {
    return TryCatchClickHouseError([&]() {
        client->Execute(*query);
    });
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus Select(Client *client, const char *query,
                                                                      SelectCallback cb) {
    return TryCatchClickHouseError([&]() {
        client->Select(query, cb);
    });
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus SelectWithQueryId(
    Client *client, const char *query, const char *query_id, SelectCallback cb) {
    return TryCatchClickHouseError([&]() {
        client->Select(query, query_id, cb);
    });
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus SelectCancelable(
    Client *client, const char *query, SelectCancelableCallback cb) {
    return TryCatchClickHouseError([&]() {
        client->SelectCancelable(query, cb);
    });
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus SelectCancelableWithQueryId(
    Client *client, const char *query, const char *query_id, SelectCancelableCallback cb) {
    return TryCatchClickHouseError([&]() {
        client->SelectCancelable(query, query_id, cb);
    });
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus Insert(Client *client, const char *table_name,
                                                                      const Block *block) {
    return TryCatchClickHouseError([&]() {
        client->Insert(table_name, *block);
    });
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus InsertWithQueryId(
    Client *client, const char *table_name, const char *query_id, const Block *block) {
    return TryCatchClickHouseError([&]() {
        client->Insert(table_name, query_id, *block);
    });
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus Ping(Client *client) {
    return TryCatchClickHouseError([&]() {
        client->Ping();
    });
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus ResetConnection(Client *client) {
    return TryCatchClickHouseError([&]() {
        client->ResetConnection();
    });
}

extern "C" __declspec(dllexport) inline ServerInfoWrapper GetServerInfo(const Client *client) {
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
    strcpy_s(name, nameLen + 1, serverInfo.name.c_str());

    const size_t timezoneLen = serverInfo.timezone.length();
    const auto timezone = new char[timezoneLen + 1];
    strcpy_s(timezone, timezoneLen + 1, serverInfo.timezone.c_str());

    const size_t displayNameLen = serverInfo.display_name.length();
    const auto display_name = new char[displayNameLen + 1];
    strcpy_s(display_name, displayNameLen + 1, serverInfo.display_name.c_str());

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

extern "C" __declspec(dllexport) inline const Endpoint *GetCurrentEndpoint(const Client *client) {
    if (const auto &optionalEndpoint = client->GetCurrentEndpoint(); optionalEndpoint.has_value()) {
        return &optionalEndpoint.value();
    } else {
        return nullptr;
    }
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus ResetConnectionEndpoint(Client *client) {
    return TryCatchClickHouseError([&]() {
        client->ResetConnectionEndpoint();
    });
}

extern "C" __declspec(dllexport) inline Client::Version GetVersion(const Client *client) {
    return client->GetVersion();
}