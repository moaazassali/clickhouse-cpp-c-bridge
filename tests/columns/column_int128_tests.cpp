#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_int128.h"

TEST_CASE("Constructed ColumnInt128 is valid") {
    const auto col = CreateColumnInt128();

    SUBCASE("Type is Int128") {
        CHECK(col->Type()->GetCode() == Type::Int128);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to ColumnInt128 and retrieving correctly") {
    const auto col = CreateColumnInt128();

    ColumnInt128Append(col, {0, 1});
    CHECK(col->At(0) == 1);
    CHECK(col->Size() == 1);

    int64_t max_int64 = std::numeric_limits<int64_t>::max();
    uint64_t max_uint64 = std::numeric_limits<uint64_t>::max();
    ColumnInt128Append(col, {max_int64, max_uint64});
    SUBCASE("Returns same value when appending int128_t max value") {
        CHECK(col->At(1) == absl::MakeInt128(max_int64, max_uint64));
        CHECK(col->Size() == 2);
    }

    int64_t min_int64 = std::numeric_limits<int64_t>::min();
    uint64_t min_uint64 = std::numeric_limits<uint64_t>::min();
    ColumnInt128Append(col, {min_int64, min_uint64});
    SUBCASE("Returns same value when appending int128_t min value") {
        CHECK(col->At(2) == absl::MakeInt128(min_int64, min_uint64));
        CHECK(col->Size() == 3);
    }
}
