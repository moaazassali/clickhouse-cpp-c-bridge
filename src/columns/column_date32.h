#pragma once

#include <clickhouse/columns/date.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnDate32 *chc_column_date32_create() {
    return new ColumnDate32();
}

extern "C" EXPORT inline void chc_column_date32_append(ColumnDate32 *column, const int32_t value) {
    column->AppendRaw(value);
}

extern "C" EXPORT inline int32_t chc_column_date32_at(const ColumnDate32 *column, const size_t index) {
    return column->RawAt(index);
}
