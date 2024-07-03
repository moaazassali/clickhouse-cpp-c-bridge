#pragma once

#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnUInt64 *chc_column_uint64_create() {
    return new ColumnUInt64();
}

extern "C" EXPORT inline void chc_column_uint64_append(ColumnUInt64 *column, const uint64_t value) {
    column->Append(value);
}

extern "C" EXPORT inline uint64_t chc_column_uint64_at(const ColumnUInt64 *column, const size_t index) {
    return column->At(index);
}
