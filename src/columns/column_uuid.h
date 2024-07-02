#pragma once

#include <clickhouse/columns/uuid.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/uuid_wrapper.h"
#include "structs/optional_wrapper.h"

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
