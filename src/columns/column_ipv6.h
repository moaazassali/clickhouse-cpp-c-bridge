#pragma once

#include <clickhouse/base/socket.h>

#include "export.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnIPv6 *chc_column_ipv6_create() {
    return new ColumnIPv6();
}

extern "C" EXPORT inline void chc_column_ipv6_append(ColumnIPv6 *column, const in6_addr value) {
    column->Append(value);
}

// returns a 16-byte array
// NOTE: the array is not on the heap; it is a copy of the struct (unlike the data in a string view from ColumnString);
// since the struct is 16 bytes, it is probably more efficient to copy it than to pass it by reference
extern "C" EXPORT inline in6_addr chc_column_ipv6_at(const ColumnIPv6 *column, const size_t index) {
    return column->At(index);
}
