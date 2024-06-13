#pragma once

#include <clickhouse/columns/date.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnDateTime64 *CreateColumnDateTime64(const size_t precision) {
    return new ColumnDateTime64(precision);
}

extern "C" EXPORT inline void ColumnDateTime64Append(ColumnDateTime64 *column, const int64_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int64_t ColumnDateTime64At(const ColumnDateTime64 *column, const size_t index) {
    return column->At(index);
}
