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

// ================================
// Nullable(UInt64)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnUInt64> *CreateColumnNullable_UInt64() {
    return new ColumnNullableT<ColumnUInt64>();
}

extern "C" EXPORT inline void ColumnNullable_UInt64_Append(ColumnNullableT<ColumnUInt64> *column,
                                                           const uint64_t value) {
    column->Append(value);
}

extern "C" EXPORT inline OptionalUInt64Wrapper ColumnNullable_UInt64_At(const ColumnNullableT<ColumnUInt64> *column,
                                                                        const size_t index) {
    const auto value = column->At(index);
    return value.has_value() ? OptionalUInt64Wrapper{true, value.value()} : OptionalUInt64Wrapper{false, 0};
}
