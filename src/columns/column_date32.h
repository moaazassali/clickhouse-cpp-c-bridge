#pragma once

#include <clickhouse/columns/date.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnDate32 *CreateColumnDate32() {
    return new ColumnDate32();
}

extern "C" EXPORT inline void ColumnDate32AppendRaw(ColumnDate32 *column, const int32_t value) {
    column->AppendRaw(value);
}

extern "C" EXPORT inline int32_t ColumnDate32RawAt(const ColumnDate32 *column, const size_t index) {
    return column->RawAt(index);
}
