#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_datetime64.h"

TEST_CASE("Constructed ColumnDateTime64 is valid") {
    const auto col = CreateColumnDateTime64(3);

    SUBCASE("Type is DateTime64") {
        CHECK(col->Type()->GetCode() == Type::DateTime64);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnDateTime64 correctly") {
    const auto col = CreateColumnDateTime64(3);

    ColumnDateTime64Append(col, 0);
    CHECK(ColumnDateTime64At(col, 0) == 0);
    CHECK(col->Size() == 1);

    ColumnDateTime64Append(col, std::numeric_limits<int64_t>::max());
    SUBCASE("Returns same value when appending int64_t max value") {
        CHECK(ColumnDateTime64At(col, 1) == std::numeric_limits<int64_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnDateTime64Append(col, std::numeric_limits<int64_t>::min());
    SUBCASE("Returns same value when appending int64_t min value") {
        CHECK(ColumnDateTime64At(col, 2) == std::numeric_limits<int64_t>::min());
        CHECK(col->Size() == 3);
    }
}
