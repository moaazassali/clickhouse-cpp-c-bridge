#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_enum16.h"

TEST_CASE("Constructed ColumnEnum16 is valid") {
    const auto col = chc_column_enum16_create();

    SUBCASE("Type is Enum16") {
        CHECK(col->Type()->GetCode() == Type::Enum16);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnEnum16 correctly") {
    const auto col = chc_column_enum16_create();

    chc_column_enum16_append(col, 1);
    CHECK(chc_column_enum16_at(col, 0) == 1);
    CHECK(col->Size() == 1);

    chc_column_enum16_append(col, std::numeric_limits<int16_t>::max());
    SUBCASE("Returns same value when appending int16_t max value") {
        CHECK(chc_column_enum16_at(col, 1) == std::numeric_limits<int16_t>::max());
        CHECK(col->Size() == 2);
    }

    chc_column_enum16_append(col, std::numeric_limits<int16_t>::min());
    SUBCASE("Returns same value when appending int16_t min value") {
        CHECK(chc_column_enum16_at(col, 2) == std::numeric_limits<int16_t>::min());
        CHECK(col->Size() == 3);
    }
}
