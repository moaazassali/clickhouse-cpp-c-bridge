#pragma once

#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt64 *chc_column_int64_create() {
    return new ColumnInt64();
}

extern "C" EXPORT inline void chc_column_int64_append(ColumnInt64 *column, const int64_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int64_t chc_column_int64_at(const ColumnInt64 *column, const size_t index) {
    return column->At(index);
}
