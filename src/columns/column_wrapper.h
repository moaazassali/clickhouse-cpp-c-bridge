#pragma once

#include <clickhouse/columns/column.h>

#include "export.h"

using namespace clickhouse;

extern "C" EXPORT inline void chc_column_free(const Column *col) {
    delete col;
}

extern "C" EXPORT inline int32_t chc_column_type_code(const Column *col) {
    return col->Type()->GetCode();
}

extern "C" EXPORT inline const char *chc_column_type_name(const Column *col) {
    // Allocate memory and copy string contents
    const auto typeName = col->Type()->GetName();
    const auto result = new char[typeName.length() + 1];
    strcpy(result, typeName.c_str());
    return result;
}

extern "C" EXPORT inline void chc_column_reserve(Column *col, const size_t new_cap) {
    col->Reserve(new_cap);
}

extern "C" EXPORT inline void chc_column_clear(Column *col) {
    col->Clear();
}

extern "C" EXPORT inline size_t chc_column_size(const Column *col) {
    return col->Size();
}
