#pragma once

#include <clickhouse/columns/enum.h>

#include "export.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnEnum16 *chc_column_enum16_create() {
    return new ColumnEnum16(Type::CreateEnum16({}));
}

extern "C" EXPORT inline void chc_column_enum16_append(ColumnEnum16 *column, const int16_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int16_t chc_column_enum16_at(const ColumnEnum16 *column, const size_t index) {
    return column->At(index);
}
