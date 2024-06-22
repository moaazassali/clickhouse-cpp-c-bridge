#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnDecimal *CreateColumnDecimal(size_t precision, size_t scale) {
    return new ColumnDecimal(precision, scale);
}

extern "C" EXPORT inline void ColumnDecimalAppend(ColumnDecimal *column, const int64_t high, const uint64_t low) {
    column->Append(absl::MakeInt128(high, low));
}

extern "C" EXPORT inline Int128Wrapper ColumnDecimalAt(const ColumnDecimal *column, const size_t index) {
    const auto value = column->At(index);
    return {Int128High64(value), Int128Low64(value)};
}
