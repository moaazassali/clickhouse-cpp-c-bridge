#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_uint64.h"

TEST_CASE("Constructed ColumnUInt64 is valid") {
    const auto col = CreateColumnUInt64();

    SUBCASE("Type is Int64") {
        CHECK(col->Type()->GetCode() == Type::UInt64);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnUInt64 correctly") {
    const auto col = CreateColumnUInt64();

    ColumnUInt64Append(col, 50);
    CHECK(ColumnUInt64At(col, 0) == 50);
    CHECK(col->Size() == 1);

    ColumnUInt64Append(col, std::numeric_limits<uint64_t>::max());
    SUBCASE("Returns same value when appending uint64_t max value") {
        CHECK(ColumnUInt64At(col, 1) == std::numeric_limits<uint64_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnUInt64Append(col, std::numeric_limits<uint64_t>::min());
    SUBCASE("Returns same value when appending uint64_t min value") {
        CHECK(ColumnUInt64At(col, 2) == std::numeric_limits<uint64_t>::min());
        CHECK(col->Size() == 3);
    }
}
