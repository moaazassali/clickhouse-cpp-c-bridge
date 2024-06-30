#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_array.h"
#include "columns/column_int8.h"
#include "utils.h"

Column *CreateNestedArray(Column *innerCol, const size_t depth) {
    Column *outerCol;

    for (size_t i = 0; i < depth; i++) {
        if (i == 0) {
            CreateColumnArray(innerCol, &outerCol);
        } else {
            innerCol = outerCol;
            CreateColumnArray(innerCol, &outerCol);
        }
    }

    return outerCol;
}

TEST_CASE("Constructed ColumnArray is valid") {
    Column *col;
    const auto [code, message] = CreateColumnArray(CreateColumnInt8(), &col);

    CHECK(code == 0);

    SUBCASE("Type is Array with valid nested type") {
        CHECK(col->Type()->GetName() == "Array(Int8)");
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }

    SUBCASE("Valid with many nested arrays") {
        auto innerCol = static_cast<Column *>(CreateColumnInt8());

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
