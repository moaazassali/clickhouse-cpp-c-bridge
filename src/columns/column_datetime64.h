#pragma once

#include <clickhouse/columns/date.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnDateTime64 *CreateColumnDateTime64(const size_t precision) {
    return new ColumnDateTime64(precision);
}

extern "C" EXPORT inline void ColumnDateTime64Append(ColumnDateTime64 *column, const int64_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int64_t ColumnDateTime64At(const ColumnDateTime64 *column, const size_t index) {
    return column->At(index);
}

// ================================
// Nullable(DateTime64)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnDateTime64> *CreateColumnNullable_DateTime64(const size_t precision) {
    return new ColumnNullableT<ColumnDateTime64>(precision);
}

extern "C" EXPORT inline void ColumnNullable_DateTime64_Append(ColumnNullableT<ColumnDateTime64> *column,
                                                               const int64_t value) {
    column->Append(value);
}

extern "C" EXPORT inline OptionalInt64Wrapper ColumnNullable_DateTime64_At(
    const ColumnNullableT<ColumnDateTime64> *column, const size_t index) {
    const auto value = column->At(index);
    return value.has_value()
               ? OptionalInt64Wrapper{true, value.value()}
               : OptionalInt64Wrapper{false, 0};
}
