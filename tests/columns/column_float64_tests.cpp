#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_float64.h"

TEST_CASE("Constructed ColumnFloat64 is valid") {
    const auto col = chc_column_float64_create();

    SUBCASE("Type is Float64") {
        CHECK(col->Type()->GetCode() == Type::Float64);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnFloat64 correctly") {
    const auto col = chc_column_float64_create();

    chc_column_float64_append(col, 1);
    CHECK(chc_column_float64_at(col, 0) == 1);
    CHECK(col->Size() == 1);

    chc_column_float64_append(col, std::numeric_limits<double_t>::max());
    SUBCASE("Returns same value when appending double_t max value") {
        CHECK(chc_column_float64_at(col, 1) == std::numeric_limits<double_t>::max());
        CHECK(col->Size() == 2);
    }

    chc_column_float64_append(col, std::numeric_limits<double_t>::min());
    SUBCASE("Returns same value when appending double_t min value") {
        CHECK(chc_column_float64_at(col, 2) == std::numeric_limits<double_t>::min());
        CHECK(col->Size() == 3);
    }
}
