#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_uint32.h"

TEST_CASE("Constructed ColumnUInt32 is valid") {
    const auto col = CreateColumnUInt32();

    SUBCASE("Type is Int32") {
        CHECK(col->Type()->GetCode() == Type::UInt32);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnUInt32 correctly") {
    const auto col = CreateColumnUInt32();

    ColumnUInt32Append(col, 50);
    CHECK(col->At(0) == 50);
    CHECK(col->Size() == 1);

    ColumnUInt32Append(col, std::numeric_limits<uint32_t>::max());
    SUBCASE("Returns same value when appending uint32_t max value") {
        CHECK(col->At(1) == std::numeric_limits<uint32_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnUInt32Append(col, std::numeric_limits<uint32_t>::min());
    SUBCASE("Returns same value when appending uint32_t min value") {
        CHECK(col->At(2) == std::numeric_limits<uint32_t>::min());
        CHECK(col->Size() == 3);
    }
}
