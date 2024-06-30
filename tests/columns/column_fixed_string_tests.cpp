#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_fixed_string.h"

TEST_CASE("Constructed ColumnFixedString is valid") {
    const auto col = CreateColumnFixedString(5);

    SUBCASE("Type is FixedString") {
        CHECK(col->Type()->GetCode() == Type::FixedString);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnFixedString correctly") {
    const auto col = CreateColumnFixedString(5);

    const auto in1 = "hello";
    const auto in2 = "world!";

    const auto res1 = ColumnFixedStringAppend(col, in1);
    const auto res2 = ColumnFixedStringAppend(col, in2);

    CHECK(res1.code == 0);
    CHECK(res2.code == -1); // validation error since in2 is 6 chars long

    CHECK(col->Size() == 1);

    const auto out1 = ColumnFixedStringAt(col, 0);

    CHECK(strncmp(out1.data, in1, out1.length) == 0);
}
