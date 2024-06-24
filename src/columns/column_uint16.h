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

// ================================
// Nullable(UInt16)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnUInt16> *CreateColumnNullable_UInt16() {
    return new ColumnNullableT<ColumnUInt16>();
}

extern "C" EXPORT inline void ColumnNullable_UInt16_Append(ColumnNullableT<ColumnUInt16> *column,
                                                           const uint16_t value) {
    column->Append(value);
}

extern "C" EXPORT inline OptionalUInt16Wrapper ColumnNullable_UInt16_At(const ColumnNullableT<ColumnUInt16> *column,
                                                                        const size_t index) {
    const auto value = column->At(index);
    return value.has_value() ? OptionalUInt16Wrapper{true, value.value()} : OptionalUInt16Wrapper{false, 0};
}
