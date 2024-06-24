#pragma once

#include "clickhouse/base/socket.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnIPv4 *CreateColumnIPv4() {
    return new ColumnIPv4();
}

extern "C" EXPORT inline void ColumnIPv4ppend(ColumnIPv4 *column, const uint32_t value) {
    column->Append(value);
}

extern "C" EXPORT inline uint32_t ColumnIPv4At(const ColumnIPv4 *column, const size_t index) {
    return column->At(index).s_addr;
}

// ================================
// Nullable(IPv4)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnIPv4> *CreateColumnNullable_IPv4() {
    return new ColumnNullableT<ColumnIPv4>();
}

extern "C" EXPORT inline void ColumnNullable_IPv4_Append(ColumnNullableT<ColumnIPv4> *column,
                                                         const uint32_t value) {
    in_addr addr{};
    addr.s_addr = value;
    column->Append(addr);
}

extern "C" EXPORT inline OptionalIPv4Wrapper ColumnNullable_IPv4_At(const ColumnNullableT<ColumnIPv4> *column,
                                                                    const size_t index) {
    const auto value = column->At(index);
    return value.has_value() ? OptionalIPv4Wrapper{true, value.value().s_addr} : OptionalIPv4Wrapper{false, 0};
}
