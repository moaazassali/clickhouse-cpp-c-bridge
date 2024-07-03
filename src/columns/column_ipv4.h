#pragma once

#include <clickhouse/base/socket.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnIPv4 *chc_column_ipv4_create() {
    return new ColumnIPv4();
}

extern "C" EXPORT inline void chc_column_ipv4_append(ColumnIPv4 *column, const uint32_t value) {
    column->Append(value);
}

extern "C" EXPORT inline uint32_t chc_column_ipv4_at(const ColumnIPv4 *column, const size_t index) {
    return column->At(index).s_addr;
}
