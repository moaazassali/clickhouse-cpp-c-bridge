#include <iostream>
#include <doctest/doctest.h>

#include <clickhouse/types/types.h>
#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/tuple.h>

#include "clickhouse/client.h"
#include "columns/column_tuple.h"

TEST_CASE("Constructed ColumnTuple is valid") {
    SUBCASE("Correctly creates tuple column if n > 0") {
        const auto col1 = new ColumnInt8();
        const auto col2 = new ColumnInt16();
        const auto col3 = new ColumnInt32();

        ColumnTuple *tupleCol;
        const auto res = CreateColumnTuple(&tupleCol, 3, col1, col2, col3);

        CHECK(res.code == 0);
        CHECK(tupleCol->Size() == 0);
        CHECK(tupleCol->Type()->GetName() == "Tuple(Int8, Int16, Int32)");
        CHECK(ColumnTupleColumnCount(tupleCol) == 3);

        CHECK(ColumnTupleColumnCount(tupleCol) == 3);
        CHECK(ColumnTupleColumnAt(tupleCol, 0)->Type()->GetCode() == Type::Int8);
        CHECK(ColumnTupleColumnAt(tupleCol, 1)->Type()->GetCode() == Type::Int16);
        CHECK(ColumnTupleColumnAt(tupleCol, 2)->Type()->GetCode() == Type::Int32);
    }

    SUBCASE("Result code is non-zero if n is less than or equal to 0") {
        ColumnTuple *tupleCol;

        const auto res1 = CreateColumnTuple(&tupleCol, 0);
        CHECK(res1.code != 0);

        const auto res2 = CreateColumnTuple(&tupleCol, -1);
        CHECK(res2.code != 0);

        const auto res3 = CreateColumnTuple(&tupleCol, 1, nullptr);
        CHECK(res3.code != 0);
    }
}

TEST_CASE("Appending to ColumnTuple increases its size") {
    const auto col1 = new ColumnInt8();
    const auto col2 = new ColumnInt16();
    const auto col3 = new ColumnInt32();

    ColumnTuple *tupleCol;
    CreateColumnTuple(&tupleCol, 3, col1, col2, col3);

    CHECK(tupleCol->Size() == 0);


    col1->Append(1);
    col2->Append(2);
    col3->Append(3);

    CHECK(tupleCol->Size() == 1);

    // can't verify retrieved values because casting to ColumnTupleT and using its methods was giving
    // segmentation fault. integration tests should be added to verify this functionality
}
