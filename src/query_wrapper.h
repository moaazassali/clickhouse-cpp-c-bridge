#pragma once

#include <clickhouse/query.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline Query * CreateQuery(const char* query, const char * query_id = nullptr) {
	return new Query(query, query_id);
}

extern "C" __declspec(dllexport) inline void FreeQuery(const Query * query) {
	delete query;
}
