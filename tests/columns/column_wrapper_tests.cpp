#include <doctest/doctest.h>
#include <clickhouse/columns/numeric.h>

#include "columns/column_wrapper.h"

TEST_CASE("Column is nullptr after being freed") {
    const auto col = new ColumnInt8();
    CHECK_NOTHROW(ColumnFree(col));
}

TEST_CASE("GetColumnType() returns correct type") {
    const auto col = new ColumnInt8();
    CHECK(ColumnType(col) == Type::Int8);
}

TEST_CASE("ReserveColumn() correctly changes capacity") {
    const auto col = new ColumnInt8();
    ColumnReserve(col, 100);
    CHECK(col->Capacity() == 100);
}

TEST_CASE("ClearColumn() clears the column") {
    const auto col = new ColumnInt8();
    col->Append(1);
    col->Append(2);
    col->Append(3);
    ColumnClear(col);
    CHECK(col->Size() == 0);
}

TEST_CASE("GetColumnSize() returns correct size") {
    const auto col = new ColumnInt8();
    col->Append(1);
    col->Append(2);
    col->Append(3);
    CHECK(ColumnSize(col) == 3);
}
