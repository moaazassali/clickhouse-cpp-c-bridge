#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_float64.h"

TEST_CASE("Constructed ColumnFloat64 is valid") {
    const auto col = CreateColumnFloat64();

    SUBCASE("Type is Float64") {
        CHECK(col->Type()->GetCode() == Type::Float64);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnFloat64 correctly") {
    const auto col = CreateColumnFloat64();

    ColumnFloat64Append(col, 1);
    CHECK(ColumnFloat64At(col, 0) == 1);
    CHECK(col->Size() == 1);

    ColumnFloat64Append(col, std::numeric_limits<double_t>::max());
    SUBCASE("Returns same value when appending double_t max value") {
        CHECK(ColumnFloat64At(col, 1) == std::numeric_limits<double_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnFloat64Append(col, std::numeric_limits<double_t>::min());
    SUBCASE("Returns same value when appending double_t min value") {
        CHECK(ColumnFloat64At(col, 2) == std::numeric_limits<double_t>::min());
        CHECK(col->Size() == 3);
    }
}
