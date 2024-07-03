#pragma once

#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnFloat32 *chc_column_float32_create() {
    return new ColumnFloat32();
}

extern "C" EXPORT inline void chc_column_float32_append(ColumnFloat32 *column, const float value) {
    column->Append(value);
}

extern "C" EXPORT inline float chc_column_float32_at(const ColumnFloat32 *column, const size_t index) {
    return column->At(index);
}
