#pragma once

#include <clickhouse/columns/decimal.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/int128_wrapper.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnDecimal *CreateColumnDecimal(const size_t precision, const size_t scale) {
    return new ColumnDecimal(precision, scale);
}

extern "C" EXPORT inline void ColumnDecimalAppend(ColumnDecimal *column, const Int128Wrapper value) {
    column->Append(absl::MakeInt128(value.high, value.low));
}

extern "C" EXPORT inline Int128Wrapper ColumnDecimalAt(const ColumnDecimal *column, const size_t index) {
    const auto value = column->At(index);
    return {Int128High64(value), Int128Low64(value)};
}
