#pragma once

#include <clickhouse/columns/string.h>
#include "structs/string_view_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnString *CreateColumnString() {
    return new ColumnString();
}

extern "C" EXPORT inline void ColumnStringAppend(ColumnString *column, const char *value) {
    column->Append(value);
}

extern "C" EXPORT inline StringViewWrapper ColumnStringAt(const ColumnString *column, const size_t index) {
    auto sv = column->At(index);
    return {sv.data(), sv.length()};
}
