#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnFloat64 *CreateColumnFloat64() {
    return new ColumnFloat64();
}

extern "C" EXPORT inline void ColumnFloat64Append(ColumnFloat64 *column, const double value) {
    column->Append(value);
}

extern "C" EXPORT inline double ColumnFloat64At(const ColumnFloat64 *column, const size_t index) {
    return column->At(index);
}

// ================================
// Nullable(Float64)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnFloat64> *CreateColumnNullable_Float64() {
    return new ColumnNullableT<ColumnFloat64>();
}

extern "C" EXPORT inline void
ColumnNullable_Float64_Append(ColumnNullableT<ColumnFloat64> *column, const double value) {
    column->Append(value);
}

extern "C" EXPORT inline OptionalFloat64Wrapper ColumnNullable_Float64_At(const ColumnNullableT<ColumnFloat64> *column,
                                                                          const size_t index) {
    const auto value = column->At(index);
    return value.has_value() ? OptionalFloat64Wrapper{true, value.value()} : OptionalFloat64Wrapper{false, 0};
}
