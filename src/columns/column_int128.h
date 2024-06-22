#pragma once

#include <clickhouse/columns/numeric.h>
#include "../structs/int128_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt128 *CreateColumnInt128() {
    return new ColumnInt128();
}

extern "C" EXPORT inline void ColumnInt128Append(ColumnInt128 *column, const int64_t high, const uint64_t low) {
    column->Append(absl::MakeInt128(high, low));
}

extern "C" EXPORT inline Int128Wrapper ColumnInt128At(const ColumnInt128 *column, const size_t index) {
    const auto value = column->At(index);
    return {Int128High64(value), Int128Low64(value)};
}
