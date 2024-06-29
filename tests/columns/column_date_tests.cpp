#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_date.h"

TEST_CASE("Constructed ColumnDate is valid") {
    const auto col = CreateColumnDate();

    SUBCASE("Type is Date") {
        CHECK(col->Type()->GetCode() == Type::Date);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnDate correctly") {
    const auto col = CreateColumnDate();

    ColumnDateAppendRaw(col, 100);
    CHECK(ColumnDateRawAt(col, 0) == 100);
    CHECK(col->Size() == 1);

    ColumnDateAppendRaw(col, std::numeric_limits<uint16_t>::max());
    SUBCASE("Returns same value when appending uint16_t max value") {
        CHECK(ColumnDateRawAt(col, 1) == std::numeric_limits<uint16_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnDateAppendRaw(col, std::numeric_limits<uint16_t>::min());
    SUBCASE("Returns same value when appending uint16_t min value") {
        CHECK(ColumnDateRawAt(col, 2) == std::numeric_limits<uint16_t>::min());
        CHECK(col->Size() == 3);
    }
}
