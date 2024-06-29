#pragma once

#include <clickhouse/columns/date.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnDate32 *CreateColumnDate32() {
    return new ColumnDate32();
}

extern "C" EXPORT inline void ColumnDate32AppendRaw(ColumnDate32 *column, const int32_t value) {
    column->AppendRaw(value);
}

extern "C" EXPORT inline int32_t ColumnDate32RawAt(const ColumnDate32 *column, const size_t index) {
    return column->RawAt(index);
}

// ================================
// Nullable(Date32)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnDate32> *CreateColumnNullable_Date32() {
    return new ColumnNullableT<ColumnDate32>();
}

extern "C" EXPORT inline void ColumnNullable_Date32_AppendRaw(ColumnNullableT<ColumnDate32> *column, const int32_t value) {
    column->AppendRaw(value);
}

extern "C" EXPORT inline OptionalInt32Wrapper ColumnNullable_Date32_RawAt(
    const ColumnNullableT<ColumnDate32> *column, const size_t index) {
    const auto value = column->RawAt(index);
    return value.has_value() ? OptionalInt32Wrapper{true, value.value()} : OptionalInt32Wrapper{false, 0};
}
