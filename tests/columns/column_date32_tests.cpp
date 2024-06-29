#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_date32.h"

TEST_CASE("Constructed ColumnDate32 is valid") {
    const auto col = CreateColumnDate32();

    SUBCASE("Type is Date32") {
        CHECK(col->Type()->GetCode() == Type::Date32);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnDate32 correctly") {
    const auto col = CreateColumnDate32();

    ColumnDate32AppendRaw(col, 100);
    CHECK(ColumnDate32RawAt(col, 0) == 100);
    CHECK(col->Size() == 1);

    ColumnDate32AppendRaw(col, std::numeric_limits<int32_t>::max());
    SUBCASE("Returns same value when appending int32_t max value") {
        CHECK(ColumnDate32RawAt(col, 1) == std::numeric_limits<int32_t>::max());
        CHECK(col->Size() == 2);
    }

    ColumnDate32AppendRaw(col, std::numeric_limits<int32_t>::min());
    SUBCASE("Returns same value when appending int32_t min value") {
        CHECK(ColumnDate32RawAt(col, 2) == std::numeric_limits<int32_t>::min());
        CHECK(col->Size() == 3);
    }
}
