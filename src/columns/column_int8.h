#pragma once

#include <clickhouse/columns/numeric.h>
#include "../structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt8 *CreateColumnInt8() {
    return new ColumnInt8();
}

extern "C" EXPORT inline void ColumnInt8Append(ColumnInt8 *column, const int8_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int8_t ColumnInt8At(const ColumnInt8 *column, const size_t index) {
    return column->At(index);
}

// ================================
// Nullable(Int8)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnInt8> *CreateColumnNullable_Int8() {
    return new ColumnNullableT<ColumnInt8>();
}

extern "C" EXPORT inline void ColumnNullable_Int8_Append(ColumnNullableT<ColumnInt8> *column, const int8_t value) {
    column->Append(value);
}

extern "C" EXPORT inline OptionalInt8Wrapper ColumnNullable_Int8_At(const ColumnNullableT<ColumnInt8> *column,
                                                                    const size_t index) {
    const auto value = column->At(index);
    return value.has_value()
               ? OptionalInt8Wrapper{true, value.value()}
               : OptionalInt8Wrapper{false, 0};
}
