#pragma once

#include <clickhouse/columns/uuid.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/uuid_wrapper.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnUUID *chc_column_uuid_create() {
    return new ColumnUUID();
}

extern "C" EXPORT inline void chc_column_uuid_append(ColumnUUID *column, const chc_uuid value) {
    column->Append(std::make_pair(value.first, value.second));
}

extern "C" EXPORT inline chc_uuid chc_column_uuid_at(const ColumnUUID *column, const size_t index) {
    const auto [first, second] = column->At(index);
    return chc_uuid{first, second};
}
