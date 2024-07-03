#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_array.h"
#include "columns/column_int8.h"
#include "columns/column_string.h"
#include "utils.h"

Column *CreateNestedArray(Column *innerCol, const size_t depth) {
    ColumnArray *outerCol;

    for (size_t i = 0; i < depth; i++) {
        if (i == 0) {
            chc_column_array_create(innerCol, &outerCol);
        } else {
            innerCol = outerCol;
            chc_column_array_create(innerCol, &outerCol);
        }
    }

    return outerCol;
}

TEST_CASE("Constructed ColumnArray is valid") {
    ColumnArray *col;
    const auto [code, message] = chc_column_array_create(chc_column_int8_create(), &col);

    CHECK(code == 0);

    SUBCASE("Type is Array with valid nested type") {
        CHECK(col->Type()->GetName() == "Array(Int8)");
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }

    SUBCASE("Valid with many nested arrays") {
        auto innerCol = static_cast<Column *>(chc_column_int8_create());

        auto outerCol = CreateNestedArray(innerCol, 1);
        CHECK(outerCol->Type()->GetName() == "Array(Int8)");

        outerCol = CreateNestedArray(innerCol, 2);
        CHECK(outerCol->Type()->GetName() == "Array(Array(Int8))");

        outerCol = CreateNestedArray(innerCol, 3);
        CHECK(outerCol->Type()->GetName() == "Array(Array(Array(Int8)))");

        outerCol = CreateNestedArray(innerCol, 4);
        CHECK(outerCol->Type()->GetName() == "Array(Array(Array(Array(Int8))))");

        outerCol = CreateNestedArray(innerCol, 5);
        CHECK(outerCol->Type()->GetName() == "Array(Array(Array(Array(Array(Int8)))))");

        outerCol = CreateNestedArray(innerCol, 10);
        CHECK(outerCol->Type()->GetName() ==
            "Array(Array(Array(Array(Array(Array(Array(Array(Array(Array(Int8))))))))))");

        outerCol = CreateNestedArray(innerCol, 100);
        // create string with 100 arrays
        std::string expected;
        for (size_t i = 0; i < 100; i++) {
            expected += "Array(";
        }
        expected += "Int8";
        for (size_t i = 0; i < 100; i++) {
            expected += ")";
        }
        CHECK(outerCol->Type()->GetName() == expected);
    }
}

TEST_CASE("ColumnArrayItemType returns correct type") {
    ColumnArray *col;
    chc_column_array_create(chc_column_int8_create(), &col);

    CHECK(col->Type()->GetCode() == Type::Array);
    CHECK(chc_column_array_item_type(col) == Type::Int8);
}

// this test is more of a sanity check to guide implementing the code that constructs appending to ColumnArray
// given the individual array columns and their offsets
TEST_CASE("Appending to ColumnArray using AddOffset() matches expected structure") {
    SUBCASE("Depth = 1") {
        const auto col1 = chc_column_int8_create();
        ColumnArray *col2;
        chc_column_array_create(col1, &col2);

        // append [1, 2, 3] to the array
        chc_column_int8_append(col1, 1);
        chc_column_int8_append(col1, 2);
        chc_column_int8_append(col1, 3);
        chc_column_array_add_offset(col2, 3);

        // append [] to the array
        chc_column_array_add_offset(col2, 0);

        // append [4, 5] to the array
        chc_column_int8_append(col1, 4);
        chc_column_int8_append(col1, 5);
        chc_column_array_add_offset(col2, 2);

        const auto typedCol2 = static_cast<ColumnArrayT<ColumnInt8> *>(col2);
        CHECK(typedCol2->At(0).Size() == 3);
        CHECK(typedCol2->At(0).At(0) == 1);
        CHECK(typedCol2->At(0).At(1) == 2);
        CHECK(typedCol2->At(0).At(2) == 3);

        CHECK(typedCol2->At(1).Size() == 0);

        CHECK(typedCol2->At(2).Size() == 2);
        CHECK(typedCol2->At(2).At(0) == 4);
        CHECK(typedCol2->At(2).At(1) == 5);
    }

    SUBCASE("Depth = 2") {
        const auto col1 = chc_column_int8_create();
        ColumnArray *col2;
        chc_column_array_create(col1, &col2);
        ColumnArray *col3;
        chc_column_array_create(col2, &col3);

        // append [[1], [], [3,4]] to the array
        chc_column_int8_append(col1, 1);
        chc_column_array_add_offset(col2, 1);
        chc_column_array_add_offset(col2, 0);
        chc_column_int8_append(col1, 3);
        chc_column_int8_append(col1, 4);
        chc_column_array_add_offset(col2, 2);
        chc_column_array_add_offset(col3, 3);

        // append [] to the array
        chc_column_array_add_offset(col3, 0);

        // append [[]] to the array
        chc_column_array_add_offset(col2, 0);
        chc_column_array_add_offset(col3, 1);

        // append [[5,6], [7]] to the array
        chc_column_int8_append(col1, 5);
        chc_column_int8_append(col1, 6);
        chc_column_array_add_offset(col2, 2);
        chc_column_int8_append(col1, 7);
        chc_column_array_add_offset(col2, 1);
        chc_column_array_add_offset(col3, 2);


        const auto typedCol3 = static_cast<ColumnArrayT<ColumnArrayT<ColumnInt8> > *>(col3);
        // [[1], [], [3,4]]
        CHECK(typedCol3->At(0).Size() == 3);
        CHECK(typedCol3->At(0).At(0).Size() == 1);
        CHECK(typedCol3->At(0).At(0).At(0) == 1);
        CHECK(typedCol3->At(0).At(1).Size() == 0);
        CHECK(typedCol3->At(0).At(2).Size() == 2);
        CHECK(typedCol3->At(0).At(2).At(0) == 3);
        CHECK(typedCol3->At(0).At(2).At(1) == 4);
        // []
        CHECK(typedCol3->At(1).Size() == 0);
        // [[]]
        CHECK(typedCol3->At(2).Size() == 1);
        CHECK(typedCol3->At(2).At(0).Size() == 0);
        // [[5,6], [7]]
        CHECK(typedCol3->At(3).Size() == 2);
        CHECK(typedCol3->At(3).At(0).Size() == 2);
        CHECK(typedCol3->At(3).At(0).At(0) == 5);
        CHECK(typedCol3->At(3).At(0).At(1) == 6);
        CHECK(typedCol3->At(3).At(1).Size() == 1);
        CHECK(typedCol3->At(3).At(1).At(0) == 7);
    }

    SUBCASE("Depth = 3") {
        const auto col1 = chc_column_int8_create();
        ColumnArray *col2;
        chc_column_array_create(col1, &col2);
        ColumnArray *col3;
        chc_column_array_create(col2, &col3);
        ColumnArray *col4;
        chc_column_array_create(col3, &col4);

        // append [  [[], [5,6], [7]]  ,  []  ,  [[]]  ,  [[2,3]]  ] to the array
        // [[], [5,6], [7]]
        chc_column_array_add_offset(col2, 0);
        chc_column_int8_append(col1, 5);
        chc_column_int8_append(col1, 6);
        chc_column_array_add_offset(col2, 2);
        chc_column_int8_append(col1, 7);
        chc_column_array_add_offset(col2, 1);
        chc_column_array_add_offset(col3, 3);
        // []
        chc_column_array_add_offset(col3, 0);
        // [[]]
        chc_column_array_add_offset(col2, 0);
        chc_column_array_add_offset(col3, 1);
        // [[2,3]]
        chc_column_int8_append(col1, 2);
        chc_column_int8_append(col1, 3);
        chc_column_array_add_offset(col2, 2);
        chc_column_array_add_offset(col3, 1);

        chc_column_array_add_offset(col4, 4);

        const auto typedCol4 = static_cast<ColumnArrayT<ColumnArrayT<ColumnArrayT<ColumnInt8> > > *>(col4);
        // [  [[], [5,6], [7]]  ,  []  ,  [[]]  ,  [[2,3]]  ]
        CHECK(typedCol4->At(0).Size() == 4);
        // [[], [5,6], [7]]
        CHECK(typedCol4->At(0).At(0).Size() == 3);
        CHECK(typedCol4->At(0).At(0).At(0).Size() == 0);
        CHECK(typedCol4->At(0).At(0).At(1).Size() == 2);
        CHECK(typedCol4->At(0).At(0).At(1).At(0) == 5);
        CHECK(typedCol4->At(0).At(0).At(1).At(1) == 6);
        CHECK(typedCol4->At(0).At(0).At(2).Size() == 1);
        // []
        CHECK(typedCol4->At(0).At(1).Size() == 0);
        // [[]]
        CHECK(typedCol4->At(0).At(2).Size() == 1);
        CHECK(typedCol4->At(0).At(2).At(0).Size() == 0);
        // [[2,3]]
        CHECK(typedCol4->At(0).At(3).Size() == 1);
        CHECK(typedCol4->At(0).At(3).At(0).Size() == 2);
        CHECK(typedCol4->At(0).At(3).At(0).At(0) == 2);
        CHECK(typedCol4->At(0).At(3).At(0).At(1) == 3);
    }
}

// again this test is more of a sanity check to guide implementing the code that retrieves from ColumnArray
// in external libraries
TEST_CASE("Retrieving from ColumnArray using GetOffset() matches expected structure") {
    SUBCASE("Depth = 1") {
        const auto base = chc_column_string_create();
        ColumnArray *a1;
        chc_column_array_create(base, &a1);

        const auto typedA1 = static_cast<ColumnArrayT<ColumnString> *>(a1);

        std::vector in1 = {"a", "b", "c"};
        std::vector<const char *> in2 = {};
        std::vector in3 = {"d", "e"};
        typedA1->Append(in1);
        typedA1->Append(in2);
        typedA1->Append(in3);

        CHECK(typedA1->Size() == 3);
        // [a, b, c]
        CHECK(chc_column_array_get_offset(a1, 0) == 0);
        // from the size and offset, we can deduce that the array range is [0,3)
        auto x = chc_column_string_at(base, 0);
        CHECK(strncmp(x.data, "a", x.length ) == 0);
        x = chc_column_string_at(base, 1);
        CHECK(strncmp(x.data, "b", x.length ) == 0);
        x = chc_column_string_at(base, 2);
        CHECK(strncmp(x.data, "c", x.length ) == 0);

        // []
        CHECK(chc_column_array_get_offset(a1, 2) == 3);

        // [d, e]
        CHECK(chc_column_array_get_offset(a1, 3) == 5);
        x = chc_column_string_at(base, 3);
        CHECK(strncmp(x.data, "d", x.length ) == 0);
        x = chc_column_string_at(base, 4);
        CHECK(strncmp(x.data, "e", x.length ) == 0);
    }

    SUBCASE("Depth = 2") {
        const auto base = new ColumnString();
        auto a1 = new ColumnArrayT<ColumnString>(make_fake_shared(base));
        auto a2 = new ColumnArrayT<ColumnArrayT<ColumnString>>(make_fake_shared(a1));

        std::vector<std::vector<const char *> > in1 = {{"a", "b", "c"}};
        std::vector<std::vector<const char *> > in2 = {};
        std::vector<std::vector<const char *> > in3 = {{}, {"e"}, {"f", "g"}};
        a2->Append(in1);
        a2->Append(in2);
        a2->Append(in3);

        CHECK(a2->Size() == 3);
        // [[a, b, c]]
        CHECK(chc_column_array_get_offset(a2, 0) == 0);
        CHECK(chc_column_array_get_offset(a1, 0) == 0);
        CHECK(chc_column_array_get_offset(a1, 1) == 3);
        // given the first and second offsets, we can deduce that the array range is [0,3)
        auto x = chc_column_string_at(base, 0);
        CHECK(strncmp(x.data, "a", x.length ) == 0);
        x = chc_column_string_at(base, 1);
        CHECK(strncmp(x.data, "b", x.length ) == 0);
        x = chc_column_string_at(base, 2);
        CHECK(strncmp(x.data, "c", x.length ) == 0);

        // []
        CHECK(chc_column_array_get_offset(a2, 1) == 1);
        CHECK(chc_column_array_get_offset(a2, 2) == 1); // since offset didn't change, array is empty

        // [[], [e], [f, g]]
        CHECK(chc_column_array_get_offset(a2, 2) == 1);
        CHECK(chc_column_array_get_offset(a2, 3) == 4); // we can deduce we have 3 elements (4-1=3)
        CHECK(chc_column_array_get_offset(a1, 1) == 3);
        CHECK(chc_column_array_get_offset(a1, 2) == 3); // since our offset = offset of next element, array is empty
        CHECK(chc_column_array_get_offset(a1, 3) == 4); // we can deduce we have 1 element (4-3=1)
        x = chc_column_string_at(base, 3);
        CHECK(strncmp(x.data, "e", x.length ) == 0);
        CHECK(chc_column_array_get_offset(a1, 4) == 6); // we can deduce we have 2 elements (6-4=2)
        x = chc_column_string_at(base, 4);
        CHECK(strncmp(x.data, "f", x.length ) == 0);
        x = chc_column_string_at(base, 5);
        CHECK(strncmp(x.data, "g", x.length ) == 0);
    }
}
