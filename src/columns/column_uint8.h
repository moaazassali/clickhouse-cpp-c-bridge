#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnUInt8 *CreateColumnUInt8() {
    return new ColumnUInt8();
}

extern "C" EXPORT inline void ColumnUInt8Append(ColumnUInt8 *column, const uint8_t value) {
    column->Append(value);
}

extern "C" EXPORT inline uint8_t ColumnUInt8At(const ColumnUInt8 *column, const size_t index) {
    return column->At(index);
}

// ================================
// Nullable(UInt8)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnUInt8> *CreateColumnNullable_UInt8() {
    return new ColumnNullableT<ColumnUInt8>();
}

extern "C" EXPORT inline void ColumnNullable_UInt8_Append(ColumnNullableT<ColumnUInt8> *column, const uint8_t value) {
    column->Append(value);
}

extern "C" EXPORT inline OptionalUInt8Wrapper ColumnNullable_UInt8_At(const ColumnNullableT<ColumnUInt8> *column,
                                                                      const size_t index) {
    const auto value = column->At(index);
    return value.has_value() ? OptionalUInt8Wrapper{true, value.value()} : OptionalUInt8Wrapper{false, 0};
}
