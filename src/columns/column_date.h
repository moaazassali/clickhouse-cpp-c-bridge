#pragma once

#include <clickhouse/columns/date.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnDate *CreateColumnDate() {
    return new ColumnDate();
}

extern "C" EXPORT inline void ColumnDateAppendRaw(ColumnDate *column, const uint16_t value) {
    column->AppendRaw(value);
}

extern "C" EXPORT inline uint16_t ColumnDateRawAt(const ColumnDate *column, const size_t index) {
    return column->RawAt(index);
}

// ================================
// Nullable(Date)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnDate> *CreateColumnNullable_Date() {
    return new ColumnNullableT<ColumnDate>();
}

extern "C" EXPORT inline void ColumnNullable_Date_AppendRaw(ColumnNullableT<ColumnDate> *column, const uint16_t value) {
    column->AppendRaw(value);
}

extern "C" EXPORT inline OptionalUInt16Wrapper ColumnNullable_Date_RawAt(
    const ColumnNullableT<ColumnDate> *column, const size_t index) {
    const auto value = column->RawAt(index);
    return value.has_value() ? OptionalUInt16Wrapper{true, value.value()} : OptionalUInt16Wrapper{false, 0};
}
