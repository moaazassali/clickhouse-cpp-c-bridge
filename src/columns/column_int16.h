#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt16 *CreateColumnInt16() {
    return new ColumnInt16();
}

extern "C" EXPORT inline void ColumnInt16Append(ColumnInt16 *column, const int16_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int16_t ColumnInt16At(const ColumnInt16 *column, const size_t index) {
    return column->At(index);
}
