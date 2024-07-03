#pragma once

#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"
#include "structs/int128_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt128 *chc_column_int128_create() {
    return new ColumnInt128();
}

extern "C" EXPORT inline void chc_column_int128_append(ColumnInt128 *column, const chc_int128 value) {
    column->Append(absl::MakeInt128(value.high, value.low));
}

extern "C" EXPORT inline chc_int128 chc_column_int128_at(const ColumnInt128 *column, const size_t index) {
    const auto value = column->At(index);
    return {Int128High64(value), Int128Low64(value)};
}
