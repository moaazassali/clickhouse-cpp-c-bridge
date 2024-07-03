#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_float32.h"

TEST_CASE("Constructed ColumnFloat32 is valid") {
    const auto col = chc_column_float32_create();

    SUBCASE("Type is Float32") {
        CHECK(col->Type()->GetCode() == Type::Float32);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnFloat32 correctly") {
    const auto col = chc_column_float32_create();

    chc_column_float32_append(col, 1);
    CHECK(chc_column_float32_at(col, 0) == 1);
    CHECK(col->Size() == 1);

    chc_column_float32_append(col, std::numeric_limits<float_t>::max());
    SUBCASE("Returns same value when appending float_t max value") {
        CHECK(chc_column_float32_at(col, 1) == std::numeric_limits<float_t>::max());
        CHECK(col->Size() == 2);
    }

    chc_column_float32_append(col, std::numeric_limits<float_t>::min());
    SUBCASE("Returns same value when appending float_t min value") {
        CHECK(chc_column_float32_at(col, 2) == std::numeric_limits<float_t>::min());
        CHECK(col->Size() == 3);
    }
}
