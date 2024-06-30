#include <doctest/doctest.h>
#include <clickhouse/types/types.h>

#include "columns/column_decimal.h"

TEST_CASE("Constructed ColumnDecimal is valid") {
    const auto col = CreateColumnDecimal(1, 0);

    SUBCASE("Type is DateTime") {
        CHECK(col->Type()->GetCode() == Type::Decimal);
    }

    SUBCASE("Size is 0") {
        CHECK(col->Size() == 0);
    }
}

TEST_CASE("Appending to and retrieving from ColumnDecimal correctly") {
    // Decimal32
    const auto col32 = CreateColumnDecimal(1, 0);

    ColumnDecimalAppend(col32, {0, std::numeric_limits<int32_t>::max()});
    SUBCASE("Returns same value when appending int32_t max to Decimal32") {
        CHECK(ColumnDecimalAt(col32, 0).high == 0);
        CHECK(ColumnDecimalAt(col32, 0).low == std::numeric_limits<int32_t>::max());
        CHECK(col32->Size() == 1);
    }

    auto low = static_cast<uint64_t>(std::numeric_limits<int32_t>::min()) | 0xFFFFFFFF00000000;
    ColumnDecimalAppend(col32, {-1, low});
    SUBCASE("Returns same value when appending int32_t min to Decimal32") {
        CHECK(ColumnDecimalAt(col32, 1).high == -1);
        CHECK(ColumnDecimalAt(col32, 1).low == low);
        CHECK(col32->Size() == 2);
    }

    ColumnDecimalAppend(col32, {0, static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) + 1});
    SUBCASE("Should overflow when appending int32_t max + 1 to Decimal32") {
        CHECK(ColumnDecimalAt(col32, 2).high == -1);
        CHECK(ColumnDecimalAt(col32, 2).low != static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) + 1);
        CHECK(static_cast<int32_t>(ColumnDecimalAt(col32, 2).low) == std::numeric_limits<int32_t>::min());
        CHECK(col32->Size() == 3);
    }

    low = 0xFFFFFFFF7FFFFFFF; // int32_t min - 1 in int64_t binary
    ColumnDecimalAppend(col32, {-1, low});
    SUBCASE("Should underflow when appending int32_t min - 1 to Decimal32") {
        CHECK(ColumnDecimalAt(col32, 3).high == 0);
        CHECK(ColumnDecimalAt(col32, 3).low != 0xFFFFFFFF7FFFFFFF);
        CHECK(static_cast<int32_t>(ColumnDecimalAt(col32, 3).low) == std::numeric_limits<int32_t>::max());
        CHECK(col32->Size() == 4);
    }


    // Decimal64
    auto col64 = CreateColumnDecimal(10, 0);

    ColumnDecimalAppend(col64, {0, std::numeric_limits<int64_t>::max()});
    SUBCASE("Returns same value when appending int64_t max to Decimal64") {
        CHECK(ColumnDecimalAt(col64, 0).high == 0);
        CHECK(ColumnDecimalAt(col64, 0).low == std::numeric_limits<int64_t>::max());
        CHECK(col64->Size() == 1);
    }

    low = static_cast<uint64_t>(std::numeric_limits<int64_t>::min());
    ColumnDecimalAppend(col64, {-1, low});
    SUBCASE("Returns same value when appending int64_t min to Decimal64") {
        CHECK(ColumnDecimalAt(col64, 1).high == -1);
        CHECK(ColumnDecimalAt(col64, 1).low == low);
        CHECK(col64->Size() == 2);
    }


    // Decimal128
    auto col128 = CreateColumnDecimal(19, 0);

    ColumnDecimalAppend(col128, {std::numeric_limits<int64_t>::max(), std::numeric_limits<uint64_t>::max()});
    SUBCASE("Returns same value when appending int128_t max to Decimal128") {
        CHECK(ColumnDecimalAt(col128, 0).high == std::numeric_limits<int64_t>::max());
        CHECK(ColumnDecimalAt(col128, 0).low == std::numeric_limits<uint64_t>::max());
        CHECK(col128->Size() == 1);
    }

    low = static_cast<uint64_t>(std::numeric_limits<int64_t>::min());
    ColumnDecimalAppend(col128, {std::numeric_limits<int64_t>::min(), std::numeric_limits<uint64_t>::min()});
    SUBCASE("Returns same value when appending int128_t min to Decimal128") {
        CHECK(ColumnDecimalAt(col128, 1).high == std::numeric_limits<int64_t>::min());
        CHECK(ColumnDecimalAt(col128, 1).low == std::numeric_limits<uint64_t>::min());
        CHECK(col128->Size() == 2);
    }
}
