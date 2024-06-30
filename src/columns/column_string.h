#pragma once

#include <clickhouse/columns/string.h>

#include "export.h"
#include "structs/string_view_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnString *CreateColumnString() {
    return new ColumnString();
}

// Append(const char* str) creates a copy of the string, so you can free 'value' right after calling this function
extern "C" EXPORT inline void ColumnStringAppend(ColumnString *column, const char *value) {
    column->Append(value);
}

// Might add AppendNoManagedLifetime() in the future for better performance as it doesn't create a copy of the string
// but the caller must free each string when freeing the ColumnString as well

extern "C" EXPORT inline StringViewWrapper ColumnStringAt(const ColumnString *column, const size_t index) {
    auto sv = column->At(index);
    return {sv.data(), sv.length()};
}
