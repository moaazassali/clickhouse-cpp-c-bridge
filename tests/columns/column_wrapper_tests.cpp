#include <doctest/doctest.h>
#include <clickhouse/columns/numeric.h>

#include "columns/column_wrapper.h"

TEST_CASE("Column is nullptr after being freed") {
    const auto col = new ColumnInt8();
    CHECK_NOTHROW(chc_column_free(col));
}

TEST_CASE("GetColumnType() returns correct type") {
    const auto col = new ColumnInt8();
    CHECK(chc_column_type(col) == Type::Int8);
}

TEST_CASE("ReserveColumn() correctly changes capacity") {
    const auto col = new ColumnInt8();
    chc_column_reserve(col, 100);
    CHECK(col->Capacity() == 100);
}

TEST_CASE("ClearColumn() clears the column") {
    const auto col = new ColumnInt8();
    col->Append(1);
    col->Append(2);
    col->Append(3);
    chc_column_clear(col);
    CHECK(col->Size() == 0);
}

TEST_CASE("GetColumnSize() returns correct size") {
    const auto col = new ColumnInt8();
    col->Append(1);
    col->Append(2);
    col->Append(3);
    CHECK(chc_column_size(col) == 3);
}
