#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_string.h"

TEST_CASE("Constructed ColumnString is valid") {
    const auto col = CreateColumnString();

    SUBCASE("Type is String") {
        CHECK(col->Type()->GetCode() == Type::String);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnString correctly") {
    const auto col = CreateColumnString();

    const auto in1 = "hello";
    const auto in2 = "world!";

    ColumnStringAppend(col, in1);
    ColumnStringAppend(col, in2);

    const auto out1 = ColumnStringAt(col, 0);
    const auto out2 = ColumnStringAt(col, 1);

    CHECK(strncmp(out1.data, in1, out1.length) == 0);
    CHECK(strncmp(out2.data, in2, out2.length) == 0);
}
