#pragma once

#include <clickhouse/columns/enum.h>

#include "export.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnEnum8 *chc_column_enum8_create() {
    return new ColumnEnum8(Type::CreateEnum8({}));
}

extern "C" EXPORT inline void chc_column_enum8_append(ColumnEnum8 *column, const int8_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int8_t chc_column_enum8_at(const ColumnEnum8 *column, const size_t index) {
    return column->At(index);
}
