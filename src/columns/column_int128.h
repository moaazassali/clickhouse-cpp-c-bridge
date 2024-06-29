#pragma once

#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"
#include "structs/int128_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt128 *CreateColumnInt128() {
    return new ColumnInt128();
}

extern "C" EXPORT inline void ColumnInt128Append(ColumnInt128 *column, const Int128Wrapper value) {
    column->Append(absl::MakeInt128(value.high, value.low));
}

extern "C" EXPORT inline Int128Wrapper ColumnInt128At(const ColumnInt128 *column, const size_t index) {
    const auto value = column->At(index);
    return {Int128High64(value), Int128Low64(value)};
}

// ================================
// Nullable(Int128)
// ================================
extern "C" EXPORT inline ColumnNullableT<ColumnInt128> *CreateColumnNullable_Int128() {
    return new ColumnNullableT<ColumnInt128>();
}

extern "C" EXPORT inline void ColumnNullable_Int128_Append(ColumnNullableT<ColumnInt128> *column, const int64_t high,
                                                           const uint64_t low) {
    column->Append(absl::MakeInt128(high, low));
}

extern "C" EXPORT inline OptionalInt128Wrapper ColumnNullable_Int128_At(const ColumnNullableT<ColumnInt128> *column,
                                                                        const size_t index) {
    const auto value = column->At(index);
    return value.has_value()
               ? OptionalInt128Wrapper{true, Int128High64(value.value()), Int128Low64(value.value())}
               : OptionalInt128Wrapper{false, 0, 0};
}
