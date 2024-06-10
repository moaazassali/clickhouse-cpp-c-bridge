#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnUInt64 *CreateColumnUInt64() {
    return new ColumnUInt64();
}

extern "C" EXPORT inline void ColumnUInt64Append(ColumnUInt64 *column, const uint64_t value) {
    column->Append(value);
}

extern "C" EXPORT inline uint64_t ColumnUInt64At(const ColumnUInt64 *column, const size_t index) {
    return column->At(index);
}
