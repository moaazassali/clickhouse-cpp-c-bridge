#pragma once

using namespace clickhouse;

extern "C" EXPORT inline void FreeColumn(const Column *col) {
    delete col;
}

extern "C" EXPORT inline int32_t GetColumnType(const Column *col) {
    return col->Type()->GetCode();
}

extern "C" EXPORT inline void ReserveColumn(Column *col, const size_t new_cap) {
    col->Reserve(new_cap);
}

extern "C" EXPORT inline void ClearColumn(Column *col) {
    col->Clear();
}
