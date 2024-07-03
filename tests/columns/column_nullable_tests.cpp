#include <doctest/doctest.h>

#include "columns/column_nullable.h"
#include "columns/column_uint8.h"
#include "columns/column_uint16.h"
#include "columns/column_uint32.h"
#include "columns/column_uint64.h"
#include "columns/column_int8.h"
#include "columns/column_int16.h"
#include "columns/column_int32.h"
#include "columns/column_int64.h"
#include "columns/column_int128.h"
#include "columns/column_uuid.h"
#include "columns/column_float32.h"
#include "columns/column_float64.h"
#include "columns/column_decimal.h"
#include "columns/column_date.h"
#include "columns/column_date32.h"
#include "columns/column_datetime.h"
#include "columns/column_datetime64.h"
#include "columns/column_enum8.h"
#include "columns/column_enum16.h"
#include "columns/column_string.h"
#include "columns/column_fixed_string.h"
#include "columns/column_ipv4.h"
#include "columns/column_ipv6.h"
#include "columns/column_wrapper.h"

TEST_CASE("Constructed ColumnNullable is valid") {
    SUBCASE("Correctly create Nullable(UInt8)") {
        auto inCol = chc_column_uint8_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(UInt8)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(UInt16)") {
        auto inCol = chc_column_uint16_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(UInt16)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(UInt32)") {
        auto inCol = chc_column_uint32_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(UInt32)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(UInt64)") {
        auto inCol = chc_column_uint64_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(UInt64)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Int8)") {
        auto inCol = chc_column_int8_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Int8)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Int16)") {
        auto inCol = chc_column_int16_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Int16)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Int32)") {
        auto inCol = chc_column_int32_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Int32)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Int64)") {
        auto inCol = chc_column_int64_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Int64)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Int128)") {
        auto inCol = chc_column_int128_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Int128)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(UUID)") {
        auto inCol = chc_column_uuid_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(UUID)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Float32)") {
        auto inCol = chc_column_float32_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Float32)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Float64)") {
        auto inCol = chc_column_float64_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Float64)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Decimal)") {
        auto inCol = chc_column_decimal_create(9, 4);
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Decimal(9,4))");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Date)") {
        auto inCol = chc_column_date_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Date)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Date32)") {
        auto inCol = chc_column_date32_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Date32)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(DateTime)") {
        auto inCol = chc_column_datetime_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(DateTime)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(DateTime64)") {
        auto inCol = chc_column_datetime64_create(3);
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(DateTime64(3))");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Enum8)") {
        auto inCol = chc_column_enum8_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Enum8())");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Enum16)") {
        auto inCol = chc_column_enum16_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Enum16())");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(String)") {
        auto inCol = chc_column_string_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(String)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(FixedString)") {
        auto inCol = chc_column_fixed_string_create(10);
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(FixedString(10))");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(IPv4)") {
        auto inCol = chc_column_ipv4_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(IPv4)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(IPv6)") {
        auto inCol = chc_column_ipv6_create();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(IPv6)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Returns non-zero result code for unsupported nullable type") {
        auto inCol = new ColumnArrayT<ColumnInt8>();
        ColumnNullable *outCol;
        auto [code, message] = chc_column_nullable_create(inCol, &outCol);
        CHECK(code == -1);
    }
}

TEST_CASE("Appending to and retrieving from ColumnNullable correctly") {
    SUBCASE("Append and retrieve from Nullable(UInt8)") {
        const auto inCol = chc_column_uint8_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = 1;
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_uint8 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_uint8 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(UInt16)") {
        const auto inCol = chc_column_uint16_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<uint16_t>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_uint16 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_uint16 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(UInt32)") {
        const auto inCol = chc_column_uint32_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<uint32_t>::max();;
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_uint32 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_uint32 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(UInt64)") {
        const auto inCol = chc_column_uint64_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<uint64_t>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_uint64 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_uint64 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(Int8)") {
        const auto inCol = chc_column_int8_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<int8_t>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_int8 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_int8 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(Int16)") {
        const auto inCol = chc_column_int16_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<int16_t>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_int16 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_int16 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(Int32)") {
        const auto inCol = chc_column_int32_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<int32_t>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_int32 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_int32 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(Int64)") {
        const auto inCol = chc_column_int64_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<int64_t>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_int64 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_int64 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(Int128)") {
        const auto inCol = chc_column_int128_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr chc_int128 in1 = {std::numeric_limits<int64_t>::max(), std::numeric_limits<uint64_t>::max()};
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_int128 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_int128 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value.high == std::numeric_limits<int64_t>::max());
        CHECK(out1->value.low == std::numeric_limits<uint64_t>::max());
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(UUID)") {
        const auto inCol = chc_column_uuid_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr chc_uuid in1 = {std::numeric_limits<uint64_t>::max(), std::numeric_limits<int64_t>::max()};
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_uuid *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_uuid *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value.first == std::numeric_limits<uint64_t>::max());
        CHECK(out1->value.second == std::numeric_limits<int64_t>::max());
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(Float32)") {
        const auto inCol = chc_column_float32_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<float>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_float32 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_float32 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(Float64)") {
        const auto inCol = chc_column_float64_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<double>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_float64 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_float64 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(Decimal)") {
        const auto inCol = chc_column_decimal_create(10, 5); // Decimal64
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr chc_int128 in1 = {0, std::numeric_limits<int64_t>::max()};
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_int128 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_int128 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value.high == 0);
        CHECK(out1->value.low == std::numeric_limits<int64_t>::max());
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(Date)") {
        const auto inCol = chc_column_date_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<uint16_t>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_uint16 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_uint16 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(Date32)") {
        const auto inCol = chc_column_date32_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<int32_t>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_int32 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_int32 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(DateTime)") {
        const auto inCol = chc_column_datetime_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<uint32_t>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_uint32 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_uint32 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(DateTime64)") {
        const auto inCol = chc_column_datetime64_create(3);
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<int64_t>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_int64 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_int64 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(Enum8)") {
        const auto inCol = chc_column_enum8_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<int8_t>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_int8 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_int8 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(Enum16)") {
        const auto inCol = chc_column_enum16_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<int16_t>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_int16 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_int16 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(String)") {
        const auto inCol = chc_column_string_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        const auto in1 = "hello";
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_string_view *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_string_view *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(strncmp(out1->value.data, in1, out1->value.length) == 0);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(FixedString)") {
        const auto inCol = chc_column_fixed_string_create(5);
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        const auto in1 = "hello";
        constexpr auto in2 = nullptr;
        const auto in3 = "world!";
        chc_column_nullable_append(outCol, in1);
        chc_column_nullable_append(outCol, in2);
        auto res = chc_column_nullable_append(outCol, in3);

        CHECK(res.code == -1); // validation error since in3 is 6 chars long
        // Identified a bug in the original clickhouse-cpp library
        // This check fails as a result
        // CHECK(GetColumnSize(outCol) == 2);

        auto out1 = static_cast<chc_optional_string_view *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_string_view *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(strncmp(out1->value.data, in1, out1->value.length) == 0);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(IPv4)") {
        const auto inCol = chc_column_ipv4_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        constexpr auto in1 = std::numeric_limits<uint32_t>::max();
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, &in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_uint32 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_uint32 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(out1->value == in1);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Append and retrieve from Nullable(IPv6)") {
        const auto inCol = chc_column_ipv6_create();
        ColumnNullable *outCol;
        chc_column_nullable_create(inCol, &outCol);

        unsigned char in1[16] = {
            0x00, 0x01, 0x02, 0x03,
            0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0A, 0x0B,
            0x0C, 0x0D, 0x0E, 0x0F
        };
        constexpr auto in2 = nullptr;
        chc_column_nullable_append(outCol, in1);
        chc_column_nullable_append(outCol, in2);

        CHECK(chc_column_size(outCol) == 2);

        auto out1 = static_cast<chc_optional_ipv6 *>(chc_column_nullable_at(outCol, 0));
        auto out2 = static_cast<chc_optional_ipv6 *>(chc_column_nullable_at(outCol, 1));

        CHECK(out1->has_value == true);
        CHECK(memcmp(&out1->value, in1, 16) == 0);
        CHECK(out2->has_value == false);
    }
    SUBCASE("Returns non-zero result code for unsupported nullable type") {
        const auto outCol = new ColumnNullableT<ColumnArrayT<ColumnInt8> >();

        constexpr auto in1 = 1;
        auto res = chc_column_nullable_append(outCol, &in1);

        CHECK(res.code == -1);

        auto value = chc_column_nullable_at(outCol, 0);
        CHECK(value == nullptr);
    }
}
