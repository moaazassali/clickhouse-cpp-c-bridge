#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt32 *CreateColumnInt32() {
    return new ColumnInt32();
}

extern "C" EXPORT inline void ColumnInt32Append(ColumnInt32 *column, const int32_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int32_t ColumnInt32At(const ColumnInt32 *column, const size_t index) {
    return column->At(index);
}

// ================================
// Nullable(Int32)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnInt32> *CreateColumnNullable_Int32() {
    return new ColumnNullableT<ColumnInt32>();
}

extern "C" EXPORT inline void ColumnNullable_Int32_Append(ColumnNullableT<ColumnInt32> *column, const int32_t value) {
    column->Append(value);
}

extern "C" EXPORT inline OptionalInt32Wrapper ColumnNullable_Int32_At(const ColumnNullableT<ColumnInt32> *column,
                                                                      const size_t index) {
    const auto value = column->At(index);
    return value.has_value()
               ? OptionalInt32Wrapper{true, value.value()}
               : OptionalInt32Wrapper{false, 0};
}
