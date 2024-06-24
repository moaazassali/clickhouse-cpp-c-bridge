#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt16 *CreateColumnInt16() {
    return new ColumnInt16();
}

extern "C" EXPORT inline void ColumnInt16Append(ColumnInt16 *column, const int16_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int16_t ColumnInt16At(const ColumnInt16 *column, const size_t index) {
    return column->At(index);
}

// ================================
// Nullable(Int16)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnInt16> *CreateColumnNullable_Int16() {
    return new ColumnNullableT<ColumnInt16>();
}

extern "C" EXPORT inline void ColumnNullable_Int16_Append(ColumnNullableT<ColumnInt16> *column, const int16_t value) {
    column->Append(value);
}

extern "C" EXPORT inline OptionalInt16Wrapper ColumnNullable_Int16_At(const ColumnNullableT<ColumnInt16> *column,
                                                                      const size_t index) {
    const auto value = column->At(index);
    return value.has_value()
               ? OptionalInt16Wrapper{true, value.value()}
               : OptionalInt16Wrapper{false, 0};
}
