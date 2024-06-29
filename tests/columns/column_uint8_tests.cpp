#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_uint8.h"

TEST_CASE("Constructed ColumnUInt8 is valid") {
    const auto col = CreateColumnUInt8();

    SUBCASE("Type is Int8") {
        CHECK(col->Type()->GetCode() == Type::UInt8);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnUInt8 correctly") {
    const auto col = CreateColumnUInt8();

    ColumnUInt8Append(col, 50);
    CHECK(col->At(0) == 50);
    CHECK(col->Size() == 1);

    ColumnUInt8Append(col, std::numeric_limits<uint8_t>::max());
    SUBCASE("Returns same value when appending uint8_t max value") {
        CHECK(col->At(1) == std::numeric_limits<uint8_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnUInt8Append(col, std::numeric_limits<uint8_t>::min());
    SUBCASE("Returns same value when appending uint8_t min value") {
        CHECK(col->At(2) == std::numeric_limits<uint8_t>::min());
        CHECK(col->Size() == 3);
    }
}
