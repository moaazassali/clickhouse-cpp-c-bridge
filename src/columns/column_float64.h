#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnFloat64 *CreateColumnFloat64() {
    return new ColumnFloat64();
}

extern "C" EXPORT inline void ColumnFloat64Append(ColumnFloat64 *column, const double value) {
    column->Append(value);
}

extern "C" EXPORT inline double ColumnFloat64At(const ColumnFloat64 *column, const size_t index) {
    return column->At(index);
}
