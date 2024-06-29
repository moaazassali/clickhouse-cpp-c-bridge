#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_datetime.h"

TEST_CASE("Constructed ColumnDateTime is valid") {
    const auto col = CreateColumnDateTime();

    SUBCASE("Type is DateTime") {
        CHECK(col->Type()->GetCode() == Type::DateTime);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnDateTime correctly") {
    const auto col = CreateColumnDateTime();

    ColumnDateTimeAppendRaw(col, 100);
    CHECK(ColumnDateTimeRawAt(col, 0) == 100);
    CHECK(col->Size() == 1);

    ColumnDateTimeAppendRaw(col, std::numeric_limits<uint32_t>::max());
    SUBCASE("Returns same value when appending uint32_t max value") {
        CHECK(ColumnDateTimeRawAt(col, 1) == std::numeric_limits<uint32_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnDateTimeAppendRaw(col, std::numeric_limits<uint32_t>::min());
    SUBCASE("Returns same value when appending uint32_t min value") {
        CHECK(ColumnDateTimeRawAt(col, 2) == std::numeric_limits<uint32_t>::min());
        CHECK(col->Size() == 3);
    }
}
