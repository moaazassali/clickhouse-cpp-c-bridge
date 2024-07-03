#pragma once

#include <clickhouse/columns/column.h>

#include "export.h"

using namespace clickhouse;

extern "C" EXPORT inline void ColumnFree(const Column *col) {
    delete col;
}

extern "C" EXPORT inline int32_t ColumnType(const Column *col) {
    return col->Type()->GetCode();
}

extern "C" EXPORT inline void ColumnReserve(Column *col, const size_t new_cap) {
    col->Reserve(new_cap);
}

extern "C" EXPORT inline void ColumnClear(Column *col) {
    col->Clear();
}

extern "C" EXPORT inline size_t ColumnSize(const Column *col) {
    return col->Size();
}
