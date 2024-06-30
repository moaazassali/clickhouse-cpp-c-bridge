#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_enum8.h"

TEST_CASE("Constructed ColumnEnum8 is valid") {
    const auto col = CreateColumnEnum8();

    SUBCASE("Type is Enum8") {
        CHECK(col->Type()->GetCode() == Type::Enum8);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnEnum8 correctly") {
    const auto col = CreateColumnEnum8();

    ColumnEnum8Append(col, 1);
    CHECK(ColumnEnum8At(col, 0) == 1);
    CHECK(col->Size() == 1);

    ColumnEnum8Append(col, std::numeric_limits<int8_t>::max());
    SUBCASE("Returns same value when appending int8_t max value") {
        CHECK(ColumnEnum8At(col, 1) == std::numeric_limits<int8_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnEnum8Append(col, std::numeric_limits<int8_t>::min());
    SUBCASE("Returns same value when appending int8_t min value") {
        CHECK(ColumnEnum8At(col, 2) == std::numeric_limits<int8_t>::min());
        CHECK(col->Size() == 3);
    }
}
