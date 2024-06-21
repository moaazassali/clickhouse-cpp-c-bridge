#pragma once

#include "../structs/uuid_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnUUID *CreateColumnUUID() {
    return new ColumnUUID();
}

extern "C" EXPORT inline void ColumnUUIDAppend(ColumnUUID *column, const uint64_t value1, const uint64_t value2) {
    column->Append(std::make_pair(value1, value2));
}

// Should we return a pointer to the UUIDWrapper instead?
extern "C" EXPORT inline UUIDWrapper ColumnUUIDAt(const ColumnUUID *column, const size_t index) {
    const auto [first, second] = column->At(index);
    return UUIDWrapper{first, second};
}
