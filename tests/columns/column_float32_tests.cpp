#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_float32.h"

TEST_CASE("Constructed ColumnFloat32 is valid") {
    const auto col = CreateColumnFloat32();

    SUBCASE("Type is Float32") {
        CHECK(col->Type()->GetCode() == Type::Float32);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnFloat32 correctly") {
    const auto col = CreateColumnFloat32();

    ColumnFloat32Append(col, 1);
    CHECK(ColumnFloat32At(col, 0) == 1);
    CHECK(col->Size() == 1);

    ColumnFloat32Append(col, std::numeric_limits<float_t>::max());
    SUBCASE("Returns same value when appending float_t max value") {
        CHECK(ColumnFloat32At(col, 1) == std::numeric_limits<float_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnFloat32Append(col, std::numeric_limits<float_t>::min());
    SUBCASE("Returns same value when appending float_t min value") {
        CHECK(ColumnFloat32At(col, 2) == std::numeric_limits<float_t>::min());
        CHECK(col->Size() == 3);
    }
}
