#pragma once

#include <clickhouse/columns/string.h>

#include "export.h"
#include "structs/string_view_wrapper.h"
#include "structs/clickhouse_result_status.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnFixedString *CreateColumnFixedString(const size_t n) {
    return new ColumnFixedString(n);
}

// Append(const char* str) creates a copy of the string, so you can free 'value' right after calling this function
extern "C" EXPORT inline ClickHouseResultStatus ColumnFixedStringAppend(ColumnFixedString *column, const char *value) {
    return TryCatchClickHouseError([&]() {
        column->Append(value);
    });
}

extern "C" EXPORT inline StringViewWrapper ColumnFixedStringAt(const ColumnFixedString *column, const size_t index) {
    auto sv = column->At(index);
    return {sv.data(), sv.length()};
}
