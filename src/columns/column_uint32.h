#pragma once

#include <clickhouse/columns/numeric.h>

#include "export.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnUInt32 *chc_column_uint32_create() {
    return new ColumnUInt32();
}

extern "C" EXPORT inline void chc_column_uint32_append(ColumnUInt32 *column, const uint32_t value) {
    column->Append(value);
}

extern "C" EXPORT inline uint32_t chc_column_uint32_at(const ColumnUInt32 *column, const size_t index) {
    return column->At(index);
}
