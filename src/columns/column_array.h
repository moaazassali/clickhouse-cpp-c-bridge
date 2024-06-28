#pragma once

#include "clickhouse/columns/array.h"

using namespace clickhouse;

inline Column *CreateInnerMostColumn(const Type::Code code, const Type::Code nullableCode,
                                     const size_t a, const size_t b) {
    Column **nestedColumn = nullptr; // for nullable columns if needed

    switch (code) {
        case Type::UInt8:
            return new ColumnArrayT<ColumnUInt8>();
        case Type::UInt16:
            return new ColumnArrayT<ColumnUInt16>();
        case Type::UInt32:
            return new ColumnArrayT<ColumnUInt32>();
        case Type::UInt64:
            return new ColumnArrayT<ColumnUInt64>();
        case Type::Int8:
            return new ColumnArrayT<ColumnInt8>();
        case Type::Int16:
            return new ColumnArrayT<ColumnInt16>();
        case Type::Int32:
            return new ColumnArrayT<ColumnInt32>();
        case Type::Int64:
            return new ColumnArrayT<ColumnInt64>();
        case Type::Int128:
            return new ColumnArrayT<ColumnInt128>();
        case Type::UUID:
            return new ColumnArrayT<ColumnUUID>();
        case Type::Float32:
            return new ColumnArrayT<ColumnFloat32>();
        case Type::Float64:
            return new ColumnArrayT<ColumnFloat64>();
        case Type::Decimal:
            return new ColumnArrayT<ColumnDecimal>(a, b);
        case Type::Date:
            return new ColumnArrayT<ColumnDate>();
        case Type::Date32:
            return new ColumnArrayT<ColumnDate32>();
        case Type::DateTime:
            return new ColumnArrayT<ColumnDateTime>();
        case Type::DateTime64:
            return new ColumnArrayT<ColumnDateTime64>(a);
        case Type::Enum8:
            return new ColumnArrayT<ColumnEnum8>(Type::CreateEnum8({}));
        case Type::Enum16:
            return new ColumnArrayT<ColumnEnum16>(Type::CreateEnum8({}));
        case Type::String:
            return new ColumnArrayT<ColumnString>();
        case Type::FixedString:
            return new ColumnArrayT<ColumnFixedString>(a);
        case Type::IPv4:
            return new ColumnArrayT<ColumnIPv4>();
        case Type::IPv6:
            return new ColumnArrayT<ColumnIPv6>();
        case Type::Nullable:
            const auto status = CreateColumnNullable(nullableCode, a, b, nestedColumn);
        // rethrow the error if not successful
            if (status.code != 0) {
                throw ValidationError(status.message);
            }
            return *nestedColumn;
        default:
            throw ValidationError(
                std::string("Provided type is not supported with Array(T) column: ") + Type::TypeName(code)
                + "=" + std::to_string(code));
    }
}

// Helper function to create nested array columns without recursive templates for C compatibility
inline Column *CreateNestedArray(const Type::Code code, const Type::Code nullableCode, const size_t depth,
                                 const size_t a, const size_t b) {
    std::shared_ptr<Column> column;
    Column *finalColumn = nullptr;

    for (size_t i = 0; i < depth; i++) {
        // create innermost column with the base type
        if (i == 0) {
            // if depth is 1, we don't want a shared_ptr since this is the final column
            if (depth == 1) {
                return CreateInnerMostColumn(code, nullableCode, a, b);
            }
            column = std::shared_ptr<Column>(CreateInnerMostColumn(code, nullableCode, a, b));
        }
        // otherwise, we create new ColumnArrayT with the previous column nested inside
        else if (i == depth - 1) {
            finalColumn = new ColumnArrayT(column);
        } else {
            column = std::make_shared<ColumnArrayT<Column> >(column);
        }
    }

    return finalColumn;
}

// For FixedString and Decimal, pass length/precision as a
// For DateTime64, pass precision and scale as a and b respectively
// For all other types, a and b does not have any effect, pass whatever you want
// Depth = 1 means Array(T)
extern "C" EXPORT inline ClickHouseResultStatus CreateNestedColumnArray(
    const Type::Code code, const Type::Code nullableCode, const size_t depth, const size_t a, const size_t b,
    Column **column) {
    return TryCatchClickHouseError([&]() {
        if (depth == 0) {
            throw ValidationError("Depth should be greater than 0");
        }
        if (code != Type::Nullable && nullableCode != Type::Void) {
            throw ValidationError("Nullable type should be Type::Void for non-nullable types");
        }

        *column = CreateNestedArray(code, nullableCode, depth, a, b);
    });
}

extern "C" EXPORT inline ClickHouseResultStatus CreateColumnArray(Column *inColumn, Column **outColumn) {
    return TryCatchClickHouseError([&]() {
        *outColumn = new ColumnArray(std::shared_ptr<Column>(inColumn));
    });
}
