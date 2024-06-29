#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_int16.h"

TEST_CASE("Constructed ColumnInt16 is valid") {
    const auto col = CreateColumnInt16();

    SUBCASE("Type is Int16") {
        CHECK(col->Type()->GetCode() == Type::Int16);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnInt16 correctly") {
    const auto col = CreateColumnInt16();

    ColumnInt16Append(col, 1);
    CHECK(ColumnInt16At(col, 0) == 1);
    CHECK(col->Size() == 1);

    ColumnInt16Append(col, std::numeric_limits<int16_t>::max());
    SUBCASE("Returns same value when appending int16_t max value") {
        CHECK(ColumnInt16At(col, 1) == std::numeric_limits<int16_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnInt16Append(col, std::numeric_limits<int16_t>::min());
    SUBCASE("Returns same value when appending int16_t min value") {
        CHECK(ColumnInt16At(col, 2) == std::numeric_limits<int16_t>::min());
        CHECK(col->Size() == 3);
    }
}
