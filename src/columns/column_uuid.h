#pragma once

#include "../structs/uuid_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnUUID *CreateColumnUUID() {
    return new ColumnUUID();
}

extern "C" EXPORT inline void ColumnUUIDAppend(ColumnUUID *column, const UUIDWrapper value) {
    column->Append(std::make_pair(value.first, value.second));
}

// Should we return a pointer to the UUIDWrapper instead?
extern "C" EXPORT inline UUIDWrapper ColumnUUIDAt(const ColumnUUID *column, const size_t index) {
    const auto [first, second] = column->At(index);
    return UUIDWrapper{first, second};
}

// ================================
// Nullable(UUID)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnUUID> *CreateColumnNullable_UUID() {
    return new ColumnNullableT<ColumnUUID>();
}

extern "C" EXPORT inline void ColumnNullable_UUID_Append(ColumnNullableT<ColumnUUID> *column,
                                                         const uint64_t value1, const uint64_t value2) {
    column->Append(std::make_pair(value1, value2));
}

extern "C" EXPORT inline OptionalUUIDWrapper ColumnNullable_UUID_At(const ColumnNullableT<ColumnUUID> *column,
                                                                    const size_t index) {
    const auto value = column->At(index);
    return value.has_value()
               ? OptionalUUIDWrapper{true, UUIDWrapper{value.value().first, value.value().second}}
               : OptionalUUIDWrapper{false, UUIDWrapper{0, 0}};
}
