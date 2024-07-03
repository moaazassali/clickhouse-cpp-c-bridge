#pragma once

#include <clickhouse/columns/numeric.h>

#include "export.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnUInt16 *chc_column_uint16_create() {
    return new ColumnUInt16();
}

extern "C" EXPORT inline void chc_column_uint16_append(ColumnUInt16 *column, const uint16_t value) {
    column->Append(value);
}

extern "C" EXPORT inline uint16_t chc_column_uint16_at(const ColumnUInt16 *column, const size_t index) {
    return column->At(index);
}
