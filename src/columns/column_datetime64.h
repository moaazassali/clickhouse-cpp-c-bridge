#pragma once

#include <clickhouse/columns/date.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnDateTime64 *chc_column_datetime64_create(const size_t precision) {
    return new ColumnDateTime64(precision);
}

extern "C" EXPORT inline void chc_column_datetime64_append(ColumnDateTime64 *column, const int64_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int64_t chc_column_datetime64_at(const ColumnDateTime64 *column, const size_t index) {
    return column->At(index);
}
