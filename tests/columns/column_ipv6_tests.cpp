#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_ipv6.h"

TEST_CASE("Constructed ColumnIPv6 is valid") {
    const auto col = chc_column_ipv6_create();

    SUBCASE("Type is IPv6") {
        CHECK(col->Type()->GetCode() == Type::IPv6);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnIPv6 correctly") {
    const auto col = chc_column_ipv6_create();

    const unsigned char value[16] = {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B,
        0x0C, 0x0D, 0x0E, 0x0F
    };
    chc_column_ipv6_append(col, value);
    const auto out = chc_column_ipv6_at(col, 0);
    CHECK(memcmp(&out, value, 16) == 0);
    CHECK(col->Size() == 1);
}
