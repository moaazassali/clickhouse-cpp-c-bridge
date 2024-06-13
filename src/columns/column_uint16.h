#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnUInt16 *CreateColumnUInt16() {
    return new ColumnUInt16();
}

extern "C" EXPORT inline void ColumnUInt16Append(ColumnUInt16 *column, const uint16_t value) {
    column->Append(value);
}

extern "C" EXPORT inline uint16_t ColumnUInt16At(const ColumnUInt16 *column, const size_t index) {
    return column->At(index);
}
