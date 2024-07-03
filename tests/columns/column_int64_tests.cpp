#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_int64.h"

TEST_CASE("Constructed ColumnInt64 is valid") {
    const auto col = chc_column_int64_create();

    SUBCASE("Type is Int64") {
        CHECK(col->Type()->GetCode() == Type::Int64);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnInt64 correctly") {
    const auto col = chc_column_int64_create();

    chc_column_int64_append(col, 1);
    CHECK(chc_column_int64_at(col, 0) == 1);
    CHECK(col->Size() == 1);

    chc_column_int64_append(col, std::numeric_limits<int64_t>::max());
    SUBCASE("Returns same value when appending int64_t max value") {
        CHECK(chc_column_int64_at(col, 1) == std::numeric_limits<int64_t>::max());
        CHECK(col->Size() == 2);
    }

    chc_column_int64_append(col, std::numeric_limits<int64_t>::min());
    SUBCASE("Returns same value when appending int64_t min value") {
        CHECK(chc_column_int64_at(col, 2) == std::numeric_limits<int64_t>::min());
        CHECK(col->Size() == 3);
    }
}
