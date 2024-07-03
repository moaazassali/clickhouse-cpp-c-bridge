#pragma once

#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnFloat64 *chc_column_float64_create() {
    return new ColumnFloat64();
}

extern "C" EXPORT inline void chc_column_float64_append(ColumnFloat64 *column, const double value) {
    column->Append(value);
}

extern "C" EXPORT inline double chc_column_float64_at(const ColumnFloat64 *column, const size_t index) {
    return column->At(index);
}
