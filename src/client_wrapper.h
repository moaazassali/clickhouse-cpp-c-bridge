#pragma once

#include <clickhouse/client.h>
#include "structs/clickhouse_result_status.h"

using namespace clickhouse;

extern "C" __declspec(dllexport) inline Client * CreateClient(const char* host) {
	return new Client(ClientOptions().SetHost(host));
}

extern "C" __declspec(dllexport) inline void FreeClient(const Client * client) {
	delete client;
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus Execute(Client * client, const Query * query) {
	return TryCatchClickHouseError([&]() {
		client->Execute(*query);
		});
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus Select(Client * client, const char* query, SelectCallback cb) {
	return TryCatchClickHouseError([&]() {
		client->Select(query, cb);
		});
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus SelectWithQueryId(Client * client, const char* query, const char* query_id, SelectCallback cb) {
	return TryCatchClickHouseError([&]() {
		client->Select(query, query_id, cb);
		});
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus SelectCancelable(Client * client, const char* query, SelectCancelableCallback cb) {
	return TryCatchClickHouseError([&]() {
		client->SelectCancelable(query, cb);
		});
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus SelectCancelableWithQueryId(Client * client, const char* query, const char* query_id, SelectCancelableCallback cb) {
	return TryCatchClickHouseError([&]() {
		client->SelectCancelable(query, query_id, cb);
		});
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus Insert(Client * client, const char* table_name, const Block * block) {
	return TryCatchClickHouseError([&]() {
		client->Insert(table_name, *block);
		});
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus InsertWithQueryId(Client * client, const char* table_name, const char* query_id, const Block * block) {
	return TryCatchClickHouseError([&]() {
		client->Insert(table_name, query_id, *block);
		});
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus Ping(Client * client) {
	return TryCatchClickHouseError([&]() {
		client->Ping();
		});
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus ResetConnection(Client * client) {
	return TryCatchClickHouseError([&]() {
		client->ResetConnection();
		});
}

extern "C" __declspec(dllexport) inline const ServerInfo & GetServerInfo(const Client * client) {
	return client->GetServerInfo();
}

extern "C" __declspec(dllexport) inline const Endpoint * GetCurrentEndpoint(const Client * client) {
	if (const auto& optionalEndpoint = client->GetCurrentEndpoint(); optionalEndpoint.has_value()) {
		return &optionalEndpoint.value();
	}
	else {
		return nullptr;
	}
}

extern "C" __declspec(dllexport) inline ClickHouseResultStatus ResetConnectionEndpoint(Client * client) {
	return TryCatchClickHouseError([&]() {
		client->ResetConnectionEndpoint();
		});
}

extern "C" __declspec(dllexport) inline Client::Version GetVersion(const Client * client) {
	return client->GetVersion();
}
