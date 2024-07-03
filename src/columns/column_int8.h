#pragma once

#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt8 *chc_column_int8_create() {
    return new ColumnInt8();
}

extern "C" EXPORT inline void chc_column_int8_append(ColumnInt8 *column, const int8_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int8_t chc_column_int8_at(const ColumnInt8 *column, const size_t index) {
    return column->At(index);
}
