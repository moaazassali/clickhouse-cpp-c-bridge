#pragma once

#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnUInt32 *CreateColumnUInt32() {
    return new ColumnUInt32();
}

extern "C" EXPORT inline void ColumnUInt32Append(ColumnUInt32 *column, const uint32_t value) {
    column->Append(value);
}

extern "C" EXPORT inline uint32_t ColumnUInt32At(const ColumnUInt32 *column, const size_t index) {
    return column->At(index);
}

// ================================
// Nullable(UInt32)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnUInt32> *CreateColumnNullable_UInt32() {
    return new ColumnNullableT<ColumnUInt32>();
}

extern "C" EXPORT inline void ColumnNullable_UInt32_Append(ColumnNullableT<ColumnUInt32> *column,
                                                           const uint32_t value) {
    column->Append(value);
}

extern "C" EXPORT inline OptionalUInt32Wrapper ColumnNullable_UInt32_At(const ColumnNullableT<ColumnUInt32> *column,
                                                                        const size_t index) {
    const auto value = column->At(index);
    return value.has_value() ? OptionalUInt32Wrapper{true, value.value()} : OptionalUInt32Wrapper{false, 0};
}
