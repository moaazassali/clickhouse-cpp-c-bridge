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

TEST_CASE("Constructed ColumnNullable is valid") {
    SUBCASE("Correctly create Nullable(UInt8)") {
        auto inCol = CreateColumnUInt8();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(UInt8)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(UInt16)") {
        auto inCol = CreateColumnUInt16();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(UInt16)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(UInt32)") {
        auto inCol = CreateColumnUInt32();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(UInt32)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(UInt64)") {
        auto inCol = CreateColumnUInt64();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(UInt64)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Int8)") {
        auto inCol = CreateColumnInt8();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Int8)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Int16)") {
        auto inCol = CreateColumnInt16();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Int16)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Int32)") {
        auto inCol = CreateColumnInt32();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Int32)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Int64)") {
        auto inCol = CreateColumnInt64();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Int64)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Int128)") {
        auto inCol = CreateColumnInt128();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Int128)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(UUID)") {
        auto inCol = CreateColumnUUID();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(UUID)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Float32)") {
        auto inCol = CreateColumnFloat32();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Float32)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Float64)") {
        auto inCol = CreateColumnFloat64();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Float64)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Decimal)") {
        auto inCol = CreateColumnDecimal(9, 4);
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Decimal(9,4))");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Date)") {
        auto inCol = CreateColumnDate();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Date)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Date32)") {
        auto inCol = CreateColumnDate32();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Date32)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(DateTime)") {
        auto inCol = CreateColumnDateTime();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(DateTime)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(DateTime64)") {
        auto inCol = CreateColumnDateTime64(3);
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(DateTime64(3))");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Enum8)") {
        auto inCol = CreateColumnEnum8();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Enum8())");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(Enum16)") {
        auto inCol = CreateColumnEnum16();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(Enum16())");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(String)") {
        auto inCol = CreateColumnString();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(String)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(FixedString)") {
        auto inCol = CreateColumnFixedString(10);
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(FixedString(10))");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(IPv4)") {
        auto inCol = CreateColumnIPv4();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(IPv4)");
        CHECK(outCol->Size() == 0);
    }
    SUBCASE("Correctly create Nullable(IPv6)") {
        auto inCol = CreateColumnIPv6();
        Column *outCol;
        auto [code, message] = CreateColumnNullable(inCol, &outCol);
        CHECK(code == 0);
        CHECK(outCol->Type()->GetName() == "Nullable(IPv6)");
        CHECK(outCol->Size() == 0);
    }
}

