#pragma once

#include <clickhouse/columns/date.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnDateTime *chc_column_datetime_create() {
    return new ColumnDateTime();
}

extern "C" EXPORT inline void chc_column_datetime_append(ColumnDateTime *column, const uint32_t value) {
    column->AppendRaw(value);
}

extern "C" EXPORT inline uint32_t chc_column_datetime_at(const ColumnDateTime *column, const size_t index) {
    return column->RawAt(index);
}
