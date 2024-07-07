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

extern "C" EXPORT inline const char *chc_query_get_text(const Query *query) {
    return query->GetText().c_str();
}

extern "C" EXPORT inline const char *chc_query_get_query_id(const Query *query) {
    return query->GetQueryID().c_str();
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

inline ProgressCallback GetProgressCallback(void (*cb)(const Progress *progress)) {
    return [cb](const Progress &progress) {
        cb(&progress);
    };
}

extern "C" EXPORT inline void chc_query_on_progress(Query *query, void (*cb)(const Progress *progress)) {
    query->OnProgress(GetProgressCallback(cb));
}

inline SelectServerLogCallback GetSelectServerLogCallback(bool (*cb)(const Block *block)) {
    return [cb](const Block &block) {
        return cb(&block);
    };
}

extern "C" EXPORT inline void chc_query_on_server_log(Query *query, bool (*cb)(const Block *block)) {
    query->OnServerLog(GetSelectServerLogCallback(cb));
}

inline ProfileEventsCallback GetProfileEventsCallback(bool (*cb)(const Block *block)) {
    return [cb](const Block &block) {
        return cb(&block);
    };
}

extern "C" EXPORT inline void chc_query_on_profile_events(Query *query, bool (*cb)(const Block *block)) {
    query->OnProfileEvents(GetProfileEventsCallback(cb));
}

inline ProfileCallbak GetProfileCallback(void (*cb)(const Profile *profile)) {
    return [cb](const Profile &profile) {
        cb(&profile);
    };
}

extern "C" EXPORT inline void chc_query_on_profile(Query *query, void (*cb)(const Profile *profile)) {
    query->OnProfile(GetProfileCallback(cb));
}
