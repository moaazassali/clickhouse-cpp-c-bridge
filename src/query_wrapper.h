#pragma once

#include <clickhouse/query.h>
#include "export.h"

using namespace clickhouse;

extern "C" EXPORT inline Query *CreateQuery(const char *query, const char *query_id = nullptr) {
    return new Query(query, query_id);
}

extern "C" EXPORT inline void FreeQuery(const Query *query) {
    delete query;
}

typedef void (*SelectCallbackWrapper)(const Block *block);

extern "C" EXPORT inline void QueryOnData(Query *query, SelectCallbackWrapper cb) {
    query->OnData([&cb](const Block &block) {
        cb(&block);
    });
}

typedef bool (*SelectCancelableCallbackWrapper)(const Block *block);

extern "C" EXPORT inline void QueryOnDataCancelable(Query *query, SelectCancelableCallbackWrapper cb) {
    query->OnDataCancelable([&cb](const Block &block) {
        return cb(&block);
    });
}

// typedef bool (*SelectServerLogCallbackWrapper)(const Block *block);
//
// extern "C" EXPORT inline void QueryOnSelectServerCallback(Query *query, SelectServerLogCallbackWrapper cb) {
//     query->OnServerLog([&cb](const Block &block) {
//         return cb(&block);
//     });
// }
//
// typedef bool (*ProfileEventsCallbackWrapper)(const Block *block);
//
// extern "C" EXPORT inline void QueryOnProfileEventsCallback(Query *query, ProfileEventsCallbackWrapper cb) {
//     query->OnProfileEvents([&cb](const Block &block) {
//         return cb(&block);
//     });
// }