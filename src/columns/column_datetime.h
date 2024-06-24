#pragma once

#include <clickhouse/columns/date.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnDateTime *CreateColumnDateTime() {
    return new ColumnDateTime();
}

extern "C" EXPORT inline void ColumnDateTimeAppendRaw(ColumnDateTime *column, const uint32_t value) {
    column->AppendRaw(value);
}

extern "C" EXPORT inline uint32_t ColumnDateTimeRawAt(const ColumnDateTime *column, const size_t index) {
    return column->RawAt(index);
}

// ================================
// Nullable(DateTime)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnDateTime> *CreateColumnNullable_DateTime() {
    return new ColumnNullableT<ColumnDateTime>();
}

extern "C" EXPORT inline void ColumnNullable_DateTime_AppendRaw(ColumnNullableT<ColumnDateTime> *column,
                                                             const uint32_t value) {
    column->AppendRaw(value);
}

extern "C" EXPORT inline OptionalUInt32Wrapper ColumnNullable_DateTime_RawAt(
    const ColumnNullableT<ColumnDateTime> *column, const size_t index) {
    const auto value = column->RawAt(index);
    return value.has_value()
               ? OptionalUInt32Wrapper{true, value.value()}
               : OptionalUInt32Wrapper{false, 0};
}
