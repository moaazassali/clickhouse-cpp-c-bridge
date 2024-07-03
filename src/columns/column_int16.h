#pragma once

#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt16 *chc_column_int16_create() {
    return new ColumnInt16();
}

extern "C" EXPORT inline void chc_column_int16_append(ColumnInt16 *column, const int16_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int16_t chc_column_int16_at(const ColumnInt16 *column, const size_t index) {
    return column->At(index);
}
