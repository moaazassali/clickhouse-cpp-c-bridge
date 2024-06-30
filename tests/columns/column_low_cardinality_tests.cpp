#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_low_cardinality.h"
#include "columns/column_string.h"
#include "columns/column_fixed_string.h"
#include "columns/column_int8.h"
#include "columns/column_wrapper.h"

TEST_CASE("Constructed ColumnLowCardinality is valid") {
    SUBCASE("Correctly create LowCardinality(String)") {
        Column *col;
        auto inCol = CreateColumnString();
        auto [code, message] = CreateColumnLowCardinality(inCol, &col);
        delete inCol;
        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(String)");
        CHECK(col->Size() == 0);
    }

    SUBCASE("Correctly create LowCardinality(FixedString)") {
        Column *col;
        auto inCol = CreateColumnFixedString(10);
        auto [code, message] = CreateColumnLowCardinality(inCol, &col);
        delete inCol;
        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(FixedString(10))");
        CHECK(col->Size() == 0);
    }

    SUBCASE("Correctly create LowCardinality(Nullable(String))") {
        Column *col;
        auto inCol = CreateColumnNullable_String();
        auto [code, message] = CreateColumnLowCardinality(inCol, &col);
        delete inCol;
        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(Nullable(String))");
        CHECK(col->Size() == 0);
    }

    SUBCASE("Correctly create LowCardinality(Nullable(FixedString))") {
        Column *col;
        auto inCol = CreateColumnNullable_FixedString(20);
        auto [code, message] = CreateColumnLowCardinality(inCol, &col);
        delete inCol;
        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(Nullable(FixedString(20)))");
        CHECK(col->Size() == 0);
    }

    SUBCASE("Return non-zero result code for unsupported nested type") {
        Column *col;
        auto [code, message] = CreateColumnLowCardinality(CreateColumnInt8(), &col);
        CHECK(code == -1);
    }

    SUBCASE("Return non-zero result code for unsupported nullable nested type") {
        Column *col;
        auto [code, message] = CreateColumnLowCardinality(CreateColumnNullable_Int8(), &col);
        CHECK(code == -1);
    }
}

TEST_CASE("Appending to and retrieving from ColumnLowCardinality correctly") {
    SUBCASE("Append and retrieve from LowCardinality(String)") {
        Column *col;
        auto inCol = CreateColumnString();
        auto [code, message] = CreateColumnLowCardinality(inCol, &col);
        delete inCol;

        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(String)");

        auto lcCol = static_cast<ColumnLowCardinality *>(col);

        auto in1 = "hello";
        auto in2 = "world!";

        auto res1 = ColumnLowCardinalityAppend(lcCol, in1);
        auto res2 = ColumnLowCardinalityAppend(lcCol, in2);

        CHECK(res1.code == 0);
        CHECK(res2.code == 0);

        auto out1 = static_cast<StringViewWrapper *>(ColumnLowCardinalityAt(lcCol, 0));
        auto out2 = static_cast<StringViewWrapper *>(ColumnLowCardinalityAt(lcCol, 1));

        CHECK(strncmp(out1->data, in1, out1->length) == 0);
        CHECK(strncmp(out2->data, in2, out2->length) == 0);
    }

    SUBCASE("Append and retrieve from LowCardinality(FixedString)") {
        Column *col;
        auto inCol = CreateColumnFixedString(5);
        auto [code, message] = CreateColumnLowCardinality(inCol, &col);
        delete inCol;

        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(FixedString(5))");

        auto lcCol = static_cast<ColumnLowCardinality *>(col);

        auto in1 = "hello";
        auto in2 = "world!";

        auto res1 = ColumnLowCardinalityAppend(lcCol, in1);
        auto res2 = ColumnLowCardinalityAppend(lcCol, in2); // causes validation error because in2 is 6 chars long

        CHECK(res1.code == 0);
        CHECK(res2.code == -1);

        auto out1 = static_cast<StringViewWrapper *>(ColumnLowCardinalityAt(lcCol, 0));
        CHECK(GetColumnSize(lcCol) == 1);

        CHECK(strncmp(out1->data, in1, out1->length) == 0);
    }

    SUBCASE("Append and retrieve from LowCardinality(Nullable(String))") {
        Column *col;
        auto inCol = CreateColumnNullable_String();
        auto [code, message] = CreateColumnLowCardinality(inCol, &col);
        delete inCol;

        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(Nullable(String))");

        auto lcCol = static_cast<ColumnLowCardinality *>(col);

        auto in1 = "hello";
        auto in2 = nullptr;

        auto res1 = ColumnLowCardinalityAppend(lcCol, in1);
        auto res2 = ColumnLowCardinalityAppend(lcCol, in2);

        CHECK(res1.code == 0);
        CHECK(res2.code == 0);

        auto out1 = static_cast<OptionalStringViewWrapper *>(ColumnLowCardinalityAt(lcCol, 0));
        auto out2 = static_cast<OptionalStringViewWrapper *>(ColumnLowCardinalityAt(lcCol, 1));

        CHECK(out1->has_value == true);
        CHECK(strncmp(out1->value.data, in1, out1->value.length) == 0);

        CHECK(out2->has_value == false);
        CHECK(out2->value.data == nullptr);
    }

    SUBCASE("Append and retrieve from LowCardinality(Nullable(FixedString))") {
        Column *col;
        auto inCol = CreateColumnNullable_FixedString(5);
        auto [code, message] = CreateColumnLowCardinality(inCol, &col);
        delete inCol;

        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(Nullable(FixedString(5)))");

        auto lcCol = static_cast<ColumnLowCardinality *>(col);

        auto in1 = "hello";
        auto in2 = "world!";
        auto in3 = nullptr;

        auto res1 = ColumnLowCardinalityAppend(lcCol, in1);
        auto res2 = ColumnLowCardinalityAppend(lcCol, in2);
        auto res3 = ColumnLowCardinalityAppend(lcCol, in3);

        CHECK(res1.code == 0);
        CHECK(res2.code == -1);
        CHECK(res3.code == 0);

        CHECK(GetColumnSize(lcCol) == 2);

        auto out1 = static_cast<OptionalStringViewWrapper *>(ColumnLowCardinalityAt(lcCol, 0));
        auto out3 = static_cast<OptionalStringViewWrapper *>(ColumnLowCardinalityAt(lcCol, 1));

        CHECK(out1->has_value == true);
        CHECK(strncmp(out1->value.data, in1, out1->value.length) == 0);

        CHECK(out3->has_value == false);
        CHECK(out3->value.data == nullptr);
    }
}
