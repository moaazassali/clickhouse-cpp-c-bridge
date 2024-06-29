#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_int8.h"

TEST_CASE("Constructed ColumnInt8 is valid") {
    const auto col = CreateColumnInt8();

    SUBCASE("Type is Int16") {
        CHECK(col->Type()->GetCode() == Type::Int8);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnInt8 correctly") {
    const auto col = CreateColumnInt8();

    ColumnInt8Append(col, 1);
    CHECK(col->At(0) == 1);
    CHECK(col->Size() == 1);

    ColumnInt8Append(col, std::numeric_limits<int8_t>::max());
    SUBCASE("Returns same value when appending int8_t max value") {
        CHECK(col->At(1) == std::numeric_limits<int8_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnInt8Append(col, std::numeric_limits<int8_t>::min());
    SUBCASE("Returns same value when appending int8_t min value") {
        CHECK(col->At(2) == std::numeric_limits<int8_t>::min());
        CHECK(col->Size() == 3);
    }
}
