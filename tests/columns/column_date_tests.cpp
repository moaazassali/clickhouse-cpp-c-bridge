#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_date.h"

TEST_CASE("Constructed ColumnDate is valid") {
    const auto col = chc_column_date_create();

    SUBCASE("Type is Date") {
        CHECK(col->Type()->GetCode() == Type::Date);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnDate correctly") {
    const auto col = chc_column_date_create();

    chc_column_date_append(col, 100);
    CHECK(chc_column_date_at(col, 0) == 100);
    CHECK(col->Size() == 1);

    chc_column_date_append(col, std::numeric_limits<uint16_t>::max());
    SUBCASE("Returns same value when appending uint16_t max value") {
        CHECK(chc_column_date_at(col, 1) == std::numeric_limits<uint16_t>::max());
        CHECK(col->Size() == 2);
    }

    chc_column_date_append(col, std::numeric_limits<uint16_t>::min());
    SUBCASE("Returns same value when appending uint16_t min value") {
        CHECK(chc_column_date_at(col, 2) == std::numeric_limits<uint16_t>::min());
        CHECK(col->Size() == 3);
    }
}
