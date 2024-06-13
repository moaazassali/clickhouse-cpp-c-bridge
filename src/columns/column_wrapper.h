#pragma once

using namespace clickhouse;

extern "C" EXPORT inline void FreeColumn(const Column *col) {
    delete col;
}

extern "C" EXPORT inline int32_t GetColumnType(const Column *col) {
    return col->Type()->GetCode();
}
