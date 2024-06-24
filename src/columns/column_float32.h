#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnFloat32 *CreateColumnFloat32() {
    return new ColumnFloat32();
}

extern "C" EXPORT inline void ColumnFloat32Append(ColumnFloat32 *column, const float value) {
    column->Append(value);
}

extern "C" EXPORT inline float ColumnFloat32At(const ColumnFloat32 *column, const size_t index) {
    return column->At(index);
}

// ================================
// Nullable(Float32)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnFloat32> *CreateColumnNullable_Float32() {
    return new ColumnNullableT<ColumnFloat32>();
}

extern "C" EXPORT inline void ColumnNullable_Float32_Append(ColumnNullableT<ColumnFloat32> *column, const float value) {
    column->Append(value);
}

extern "C" EXPORT inline OptionalFloat32Wrapper ColumnNullable_Float32_At(const ColumnNullableT<ColumnFloat32> *column,
                                                                          const size_t index) {
    const auto value = column->At(index);
    return value.has_value() ? OptionalFloat32Wrapper{true, value.value()} : OptionalFloat32Wrapper{false, 0};
}
