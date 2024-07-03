#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_int8.h"

TEST_CASE("Constructed ColumnInt8 is valid") {
    const auto col = chc_column_int8_create();

    SUBCASE("Type is Int8") {
        CHECK(col->Type()->GetCode() == Type::Int8);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnInt8 correctly") {
    const auto col = chc_column_int8_create();

    chc_column_int8_append(col, 1);
    CHECK(chc_column_int8_at(col, 0) == 1);
    CHECK(col->Size() == 1);

    chc_column_int8_append(col, std::numeric_limits<int8_t>::max());
    SUBCASE("Returns same value when appending int8_t max value") {
        CHECK(chc_column_int8_at(col, 1) == std::numeric_limits<int8_t>::max());
        CHECK(col->Size() == 2);
    }

    chc_column_int8_append(col, std::numeric_limits<int8_t>::min());
    SUBCASE("Returns same value when appending int8_t min value") {
        CHECK(chc_column_int8_at(col, 2) == std::numeric_limits<int8_t>::min());
        CHECK(col->Size() == 3);
    }
}
