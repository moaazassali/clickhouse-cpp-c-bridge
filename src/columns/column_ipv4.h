#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnIPv4 *CreateColumnIPv4() {
    return new ColumnIPv4();
}

extern "C" EXPORT inline void ColumnIPv4ppend(ColumnIPv4 *column, const uint32_t value) {
    column->Append(value);
}
