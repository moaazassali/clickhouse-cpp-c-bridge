#pragma once

#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt64 *CreateColumnInt64() {
    return new ColumnInt64();
}

extern "C" EXPORT inline void ColumnInt64Append(ColumnInt64 *column, const int64_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int64_t ColumnInt64At(const ColumnInt64 *column, const size_t index) {
    return column->At(index);
}

// ================================
// Nullable(Int64)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnInt64> *CreateColumnNullable_Int64() {
    return new ColumnNullableT<ColumnInt64>();
}

extern "C" EXPORT inline void ColumnNullable_Int64_Append(ColumnNullableT<ColumnInt64> *column, const int64_t value) {
    column->Append(value);
}

extern "C" EXPORT inline OptionalInt64Wrapper ColumnNullable_Int64_At(const ColumnNullableT<ColumnInt64> *column,
                                                                      const size_t index) {
    const auto value = column->At(index);
    return value.has_value()
               ? OptionalInt64Wrapper{true, value.value()}
               : OptionalInt64Wrapper{false, 0};
}
