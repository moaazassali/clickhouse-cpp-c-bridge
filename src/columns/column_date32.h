#pragma once

#include <clickhouse/columns/date.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnDate32 * CreateColumnDate32() {
    return new ColumnDate32();
}

extern "C" EXPORT inline void ColumnDateAppendRaw(ColumnDate32 * column, const int32_t value) {
    column->AppendRaw(value);
}
