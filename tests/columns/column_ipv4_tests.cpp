#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_ipv4.h"

TEST_CASE("Constructed ColumnIPv4 is valid") {
    const auto col = CreateColumnIPv4();

    SUBCASE("Type is IPv4") {
        CHECK(col->Type()->GetCode() == Type::IPv4);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnIPv4 correctly") {
    const auto col = CreateColumnIPv4();

    ColumnIPv4ppend(col, 50);
    CHECK(ColumnIPv4At(col, 0) == 50);
    CHECK(col->Size() == 1);

    ColumnIPv4ppend(col, std::numeric_limits<uint32_t>::max());
    SUBCASE("Returns same value when appending uint32_t max value") {
        CHECK(ColumnIPv4At(col, 1) == std::numeric_limits<uint32_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnIPv4ppend(col, std::numeric_limits<uint32_t>::min());
    SUBCASE("Returns same value when appending uint32_t min value") {
        CHECK(ColumnIPv4At(col, 2) == std::numeric_limits<uint32_t>::min());
        CHECK(col->Size() == 3);
    }
}
