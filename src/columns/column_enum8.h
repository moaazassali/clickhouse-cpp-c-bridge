#pragma once

#include <clickhouse/columns/enum.h>

#include "export.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnEnum8 *CreateColumnEnum8() {
    return new ColumnEnum8(Type::CreateEnum8({}));
}

extern "C" EXPORT inline void ColumnEnum8Append(ColumnEnum8 *column, const int8_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int8_t ColumnEnum8At(const ColumnEnum8 *column, const size_t index) {
    return column->At(index);
}
