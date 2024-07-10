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

    in6_addr value = {};
    value.u = {0x20, 0x01, 0x0d, 0xb8, 0x85, 0xa3, 0x08, 0x96, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x2e, 0x03, 0x70};
    chc_column_ipv6_append(col, value);
    const auto out = chc_column_ipv6_at(col, 0);
    CHECK(memcmp(&out, &value, 16) == 0);
    CHECK(col->Size() == 1);
}
