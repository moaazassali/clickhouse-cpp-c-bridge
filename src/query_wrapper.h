#pragma once

#include <clickhouse/query.h>

#include "export.h"

using namespace clickhouse;

extern "C" EXPORT inline Query *chc_query_create(const char *query, const char *query_id = nullptr) {
    return new Query(query, query_id);
}

extern "C" EXPORT inline void chc_query_free(const Query *query) {
    delete query;
}

inline SelectCallback GetSelectCallback(void (*cb)(const Block *block)) {
    return [cb](const Block &block) {
        cb(&block);
    };
}

extern "C" EXPORT inline void chc_query_on_data(Query *query, void (*cb)(const Block *block)) {
    query->OnData(GetSelectCallback(cb));
}

inline SelectCancelableCallback GetSelectCancelableCallback(bool (*cb)(const Block *block)) {
    return [cb](const Block &block) {
        return cb(&block);
    };
}

extern "C" EXPORT inline void chc_query_on_data_cancelable(Query *query, bool (*cb)(const Block *block)) {
    query->OnDataCancelable(GetSelectCancelableCallback(cb));
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
