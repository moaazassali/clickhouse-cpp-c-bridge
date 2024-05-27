#pragma once

#include <clickhouse/columns/date.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnDate * CreateColumnDate() {
    return new ColumnDate();
}

extern "C" EXPORT inline void ColumnDateAppendRaw(ColumnDate * column, const uint16_t value) {
    column->AppendRaw(value);
}
