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
