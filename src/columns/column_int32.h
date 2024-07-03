#pragma once

#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt32 *chc_column_int32_create() {
    return new ColumnInt32();
}

extern "C" EXPORT inline void chc_column_int32_append(ColumnInt32 *column, const int32_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int32_t chc_column_int32_at(const ColumnInt32 *column, const size_t index) {
    return column->At(index);
}
