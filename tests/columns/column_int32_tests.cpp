#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_int32.h"

TEST_CASE("Constructed ColumnInt32 is valid") {
    const auto col = CreateColumnInt32();

    SUBCASE("Type is Int32") {
        CHECK(col->Type()->GetCode() == Type::Int32);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnInt32 correctly") {
    const auto col = CreateColumnInt32();

    ColumnInt32Append(col, 1);
    CHECK(ColumnInt32At(col, 0) == 1);
    CHECK(col->Size() == 1);

    ColumnInt32Append(col, std::numeric_limits<int32_t>::max());
    SUBCASE("Returns same value when appending int32_t max value") {
        CHECK(ColumnInt32At(col, 1) == std::numeric_limits<int32_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnInt32Append(col, std::numeric_limits<int32_t>::min());
    SUBCASE("Returns same value when appending int32_t min value") {
        CHECK(ColumnInt32At(col, 2) == std::numeric_limits<int32_t>::min());
        CHECK(col->Size() == 3);
    }
}
