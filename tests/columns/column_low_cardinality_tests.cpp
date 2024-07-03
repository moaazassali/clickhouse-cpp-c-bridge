#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_low_cardinality.h"
#include "columns/column_string.h"
#include "columns/column_fixed_string.h"
#include "columns/column_int8.h"
#include "columns/column_wrapper.h"
#include "columns/column_nullable.h"

TEST_CASE("Constructed ColumnLowCardinality is valid") {
    SUBCASE("Correctly create LowCardinality(String)") {
        Column *col;
        auto inCol = chc_column_string_create();
        auto [code, message] = chc_column_low_cardinality_create(inCol, &col);
        delete inCol;
        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(String)");
        CHECK(col->Size() == 0);
    }

    SUBCASE("Correctly create LowCardinality(FixedString)") {
        Column *col;
        auto inCol = chc_column_fixed_string_create(10);
        auto [code, message] = chc_column_low_cardinality_create(inCol, &col);
        delete inCol;
        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(FixedString(10))");
        CHECK(col->Size() == 0);
    }

    SUBCASE("Correctly create LowCardinality(Nullable(String))") {
        Column *col;
        auto inNullCol = chc_column_string_create();
        ColumnNullable *inLcCol;
        chc_column_nullable_create(inNullCol, &inLcCol);
        auto [code, message] = chc_column_low_cardinality_create(inLcCol, &col);
        delete inNullCol;
        delete inLcCol;

        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(Nullable(String))");
        CHECK(col->Size() == 0);
    }

    SUBCASE("Correctly create LowCardinality(Nullable(FixedString))") {
        Column *col;
        auto inNullCol = chc_column_fixed_string_create(20);
        ColumnNullable *inLcCol;
        chc_column_nullable_create(inNullCol, &inLcCol);
        auto [code, message] = chc_column_low_cardinality_create(inLcCol, &col);
        delete inNullCol;
        delete inLcCol;

        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(Nullable(FixedString(20)))");
        CHECK(col->Size() == 0);
    }

    SUBCASE("Return non-zero result code for unsupported nested type") {
        Column *col;
        auto [code, message] = chc_column_low_cardinality_create(chc_column_int8_create(), &col);
        CHECK(code == -1);
    }

    SUBCASE("Return non-zero result code for unsupported nullable nested type") {
        ColumnNullable *nullCol;
        chc_column_nullable_create(chc_column_int8_create(), &nullCol);
        Column *col;
        auto [code, message] = chc_column_low_cardinality_create(nullCol, &col);
        CHECK(code == -1);
    }
}

TEST_CASE("Appending to and retrieving from ColumnLowCardinality correctly") {
    SUBCASE("Append and retrieve from LowCardinality(String)") {
        Column *col;
        auto inCol = chc_column_string_create();
        auto [code, message] = chc_column_low_cardinality_create(inCol, &col);
        delete inCol;

        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(String)");

        auto lcCol = static_cast<ColumnLowCardinality *>(col);

        auto in1 = "hello";
        auto in2 = "world!";

        auto res1 = chc_column_low_cardinality_append(lcCol, in1);
        auto res2 = chc_column_low_cardinality_append(lcCol, in2);

        CHECK(res1.code == 0);
        CHECK(res2.code == 0);

        auto out1 = static_cast<chc_string_view *>(chc_column_low_cardinality_at(lcCol, 0));
        auto out2 = static_cast<chc_string_view *>(chc_column_low_cardinality_at(lcCol, 1));

        CHECK(strncmp(out1->data, in1, out1->length) == 0);
        CHECK(strncmp(out2->data, in2, out2->length) == 0);
    }

    SUBCASE("Append and retrieve from LowCardinality(FixedString)") {
        Column *col;
        auto inCol = chc_column_fixed_string_create(5);
        auto [code, message] = chc_column_low_cardinality_create(inCol, &col);
        delete inCol;

        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(FixedString(5))");

        auto lcCol = static_cast<ColumnLowCardinality *>(col);

        auto in1 = "hello";
        auto in2 = "world!";

        auto res1 = chc_column_low_cardinality_append(lcCol, in1);
        auto res2 = chc_column_low_cardinality_append(lcCol, in2); // causes validation error because in2 is 6 chars long

        CHECK(res1.code == 0);
        CHECK(res2.code == -1);

        auto out1 = static_cast<chc_string_view *>(chc_column_low_cardinality_at(lcCol, 0));
        CHECK(chc_column_size(lcCol) == 1);

        CHECK(strncmp(out1->data, in1, out1->length) == 0);
    }

    SUBCASE("Append and retrieve from LowCardinality(Nullable(String))") {
        Column *col;
        auto inNullCol = chc_column_string_create();
        ColumnNullable *inLcCol;
        chc_column_nullable_create(inNullCol, &inLcCol);
        auto [code, message] = chc_column_low_cardinality_create(inLcCol, &col);
        delete inNullCol;
        delete inLcCol;

        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(Nullable(String))");

        auto lcCol = static_cast<ColumnLowCardinality *>(col);

        auto in1 = "hello";
        auto in2 = nullptr;

        auto res1 = chc_column_low_cardinality_append(lcCol, in1);
        auto res2 = chc_column_low_cardinality_append(lcCol, in2);

        CHECK(res1.code == 0);
        CHECK(res2.code == 0);

        auto out1 = static_cast<chc_optional_string_view *>(chc_column_low_cardinality_at(lcCol, 0));
        auto out2 = static_cast<chc_optional_string_view *>(chc_column_low_cardinality_at(lcCol, 1));

        CHECK(out1->has_value == true);
        CHECK(strncmp(out1->value.data, in1, out1->value.length) == 0);

        CHECK(out2->has_value == false);
        CHECK(out2->value.data == nullptr);
    }

    SUBCASE("Append and retrieve from LowCardinality(Nullable(FixedString))") {
        Column *col;
        auto inNullCol = chc_column_fixed_string_create(5);
        ColumnNullable *inLcCol;
        chc_column_nullable_create(inNullCol, &inLcCol);
        auto [code, message] = chc_column_low_cardinality_create(inLcCol, &col);
        delete inNullCol;
        delete inLcCol;

        CHECK(code == 0);
        CHECK(col->Type()->GetName() == "LowCardinality(Nullable(FixedString(5)))");

        auto lcCol = static_cast<ColumnLowCardinality *>(col);

        auto in1 = "hello";
        auto in2 = "world!";
        auto in3 = nullptr;

        auto res1 = chc_column_low_cardinality_append(lcCol, in1);
        auto res2 = chc_column_low_cardinality_append(lcCol, in2);
        auto res3 = chc_column_low_cardinality_append(lcCol, in3);

        CHECK(res1.code == 0);
        CHECK(res2.code == -1);
        CHECK(res3.code == 0);

        CHECK(chc_column_size(lcCol) == 2);

        auto out1 = static_cast<chc_optional_string_view *>(chc_column_low_cardinality_at(lcCol, 0));
        auto out3 = static_cast<chc_optional_string_view *>(chc_column_low_cardinality_at(lcCol, 1));

        CHECK(out1->has_value == true);
        CHECK(strncmp(out1->value.data, in1, out1->value.length) == 0);

        CHECK(out3->has_value == false);
        CHECK(out3->value.data == nullptr);
    }
}
