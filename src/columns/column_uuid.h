#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnUUID *CreateColumnUUID() {
    return new ColumnUUID();
}

extern "C" EXPORT inline void ColumnUUIDAppend(ColumnUUID *column, const uint64_t value1, const uint64_t value2) {
    column->Append(std::make_pair(value1, value2));
}
