#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_ipv4.h"

TEST_CASE("Constructed ColumnIPv4 is valid") {
    const auto col = chc_column_ipv4_create();

    SUBCASE("Type is IPv4") {
        CHECK(col->Type()->GetCode() == Type::IPv4);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnIPv4 correctly") {
    const auto col = chc_column_ipv4_create();

    chc_column_ipv4_append(col, 50);
    CHECK(chc_column_ipv4_at(col, 0) == 50);
    CHECK(col->Size() == 1);

    chc_column_ipv4_append(col, std::numeric_limits<uint32_t>::max());
    SUBCASE("Returns same value when appending uint32_t max value") {
        CHECK(chc_column_ipv4_at(col, 1) == std::numeric_limits<uint32_t>::max());
        CHECK(col->Size() == 2);
    }

    chc_column_ipv4_append(col, std::numeric_limits<uint32_t>::min());
    SUBCASE("Returns same value when appending uint32_t min value") {
        CHECK(chc_column_ipv4_at(col, 2) == std::numeric_limits<uint32_t>::min());
        CHECK(col->Size() == 3);
    }
}
