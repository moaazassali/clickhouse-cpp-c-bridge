#pragma once

#include <clickhouse/query.h>
#include "export.h"

using namespace clickhouse;

extern "C" EXPORT inline Query * CreateQuery(const char* query, const char * query_id = nullptr) {
	return new Query(query, query_id);
}

extern "C" EXPORT inline void FreeQuery(const Query * query) {
	delete query;
}
