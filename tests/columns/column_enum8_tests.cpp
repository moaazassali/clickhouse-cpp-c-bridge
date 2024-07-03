#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_enum8.h"

TEST_CASE("Constructed ColumnEnum8 is valid") {
    const auto col = chc_column_enum8_create();

    SUBCASE("Type is Enum8") {
        CHECK(col->Type()->GetCode() == Type::Enum8);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnEnum8 correctly") {
    const auto col = chc_column_enum8_create();

    chc_column_enum8_append(col, 1);
    CHECK(chc_column_enum8_at(col, 0) == 1);
    CHECK(col->Size() == 1);

    chc_column_enum8_append(col, std::numeric_limits<int8_t>::max());
    SUBCASE("Returns same value when appending int8_t max value") {
        CHECK(chc_column_enum8_at(col, 1) == std::numeric_limits<int8_t>::max());
        CHECK(col->Size() == 2);
    }

    chc_column_enum8_append(col, std::numeric_limits<int8_t>::min());
    SUBCASE("Returns same value when appending int8_t min value") {
        CHECK(chc_column_enum8_at(col, 2) == std::numeric_limits<int8_t>::min());
        CHECK(col->Size() == 3);
    }
}
