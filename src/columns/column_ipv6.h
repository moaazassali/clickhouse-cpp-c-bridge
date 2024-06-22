#pragma once

using namespace clickhouse;

extern "C" EXPORT inline ColumnIPv6 *CreateColumnIPv6() {
    return new ColumnIPv6();
}

extern "C" EXPORT inline void ColumnIPv6Append(ColumnIPv6 *column, const unsigned char value[16]) {
    in6_addr addr{};
    for (int i = 0; i < 16; i++) {
        addr.s6_addr[i] = value[i];
    }
    column->Append(addr);
}

// returns a 16-byte array
// NOTE: the array is owned by the ColumnIPv6 and will be invalid when the column is freed
extern "C" EXPORT inline unsigned char *ColumnIPv6At(const ColumnIPv6 *column, const size_t index) {
    return column->At(index).s6_addr;
}
