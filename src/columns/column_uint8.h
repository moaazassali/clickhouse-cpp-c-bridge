#pragma once

#include <clickhouse/columns/numeric.h>

#include "export.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnUInt8 *chc_column_uint8_create() {
    return new ColumnUInt8();
}

extern "C" EXPORT inline void chc_column_uint8_append(ColumnUInt8 *column, const uint8_t value) {
    column->Append(value);
}

extern "C" EXPORT inline uint8_t chc_column_uint8_at(const ColumnUInt8 *column, const size_t index) {
    return column->At(index);
}
