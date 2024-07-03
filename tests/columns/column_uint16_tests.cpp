#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_uint16.h"

TEST_CASE("Constructed ColumnUInt16 is valid") {
    const auto col = chc_column_uint16_create();

    SUBCASE("Type is Int16") {
        CHECK(col->Type()->GetCode() == Type::UInt16);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnUInt16 correctly") {
    const auto col = chc_column_uint16_create();

    chc_column_uint16_append(col, 50);
    CHECK(chc_column_uint16_at(col, 0) == 50);
    CHECK(col->Size() == 1);

    chc_column_uint16_append(col, std::numeric_limits<uint16_t>::max());
    SUBCASE("Returns same value when appending uint16_t max value") {
        CHECK(chc_column_uint16_at(col, 1) == std::numeric_limits<uint16_t>::max());
        CHECK(col->Size() == 2);
    }

    chc_column_uint16_append(col, std::numeric_limits<uint16_t>::min());
    SUBCASE("Returns same value when appending uint16_t min value") {
        CHECK(chc_column_uint16_at(col, 2) == std::numeric_limits<uint16_t>::min());
        CHECK(col->Size() == 3);
    }
}
