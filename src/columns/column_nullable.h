#pragma once

#include <clickhouse/columns/nullable.h>
#include <clickhouse/types/types.h>
#include <clickhouse/base/socket.h>

#include "export.h"
#include "utils.h"
#include "structs/clickhouse_result_status.h"
#include "structs/int128_wrapper.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

// inColumn should not be freed after calling this method as Nullable uses it directly
// But we still keep memory management of inColumn the responsibility of the caller side
// So make sure to free inColumn after freeing outColumn (or whenever appropriate otherwise)
// inColumn should ideally be hidden from the end user
extern "C" EXPORT inline chc_result_status chc_column_nullable_create(Column *inColumn, ColumnNullable **outColumn) {
    const auto type = inColumn->Type();

    return TryCatchClickHouseError([&]() {
        switch (type->GetCode()) {
            case Type::UInt8:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnUInt8 *>(inColumn)));
                break;
            case Type::UInt16:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnUInt16 *>(inColumn)));
                break;
            case Type::UInt32:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnUInt32 *>(inColumn)));
                break;
            case Type::UInt64:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnUInt64 *>(inColumn)));
                break;
            case Type::Int8:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnInt8 *>(inColumn)));
                break;
            case Type::Int16:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnInt16 *>(inColumn)));
                break;
            case Type::Int32:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnInt32 *>(inColumn)));
                break;
            case Type::Int64:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnInt64 *>(inColumn)));
                break;
            case Type::Int128:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnInt128 *>(inColumn)));
                break;
            case Type::UUID:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnUUID *>(inColumn)));
                break;
            case Type::Float32:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnFloat32 *>(inColumn)));
                break;
            case Type::Float64:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnFloat64 *>(inColumn)));
                break;
            case Type::Decimal:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnDecimal *>(inColumn)));
                break;
            case Type::Date:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnDate *>(inColumn)));
                break;
            case Type::Date32:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnDate32 *>(inColumn)));
                break;
            case Type::DateTime:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnDateTime *>(inColumn)));
                break;
            case Type::DateTime64:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnDateTime64 *>(inColumn)));
                break;
            case Type::Enum8:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnEnum8 *>(inColumn)));
                break;
            case Type::Enum16:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnEnum16 *>(inColumn)));
                break;
            case Type::String:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnString *>(inColumn)));
                break;
            case Type::FixedString:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnFixedString *>(inColumn)));
                break;
            case Type::IPv4:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnIPv4 *>(inColumn)));
                break;
            case Type::IPv6:
                *outColumn = new ColumnNullableT(make_fake_shared(static_cast<ColumnIPv6 *>(inColumn)));
                break;

            default:
                throw ValidationError(
                    std::string("Provided type is not supported for Nullable columns: ") +
                    type->GetName() + "=" + std::to_string(type->GetCode()));
        }
    });
}

template<typename T>
ColumnNullableT<T> *static_cast_column_nullable(ColumnNullable *column) {
    return dynamic_cast<ColumnNullableT<T> *>(column);
}

// Pass nullptr to append a NULL value
extern "C" EXPORT inline chc_result_status chc_column_nullable_append(ColumnNullable *column, const void *value) {
    return TryCatchClickHouseError([&]() {
        const auto nestedType = column->Nested()->Type();

        switch (nestedType->GetCode()) {
            case Type::UInt8: {
                const auto derivedColumn = static_cast_column_nullable<ColumnUInt8>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const uint8_t *>(value)));
                break;
            }
            case Type::UInt16: {
                const auto derivedColumn = static_cast_column_nullable<ColumnUInt16>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const uint16_t *>(value)));
                break;
            }
            case Type::UInt32: {
                const auto derivedColumn = static_cast_column_nullable<ColumnUInt32>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const uint32_t *>(value)));
                break;
            }
            case Type::UInt64: {
                const auto derivedColumn = static_cast_column_nullable<ColumnUInt64>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const uint64_t *>(value)));
                break;
            }
            case Type::Int8: {
                const auto derivedColumn = static_cast_column_nullable<ColumnInt8>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int8_t *>(value)));
                break;
            }
            case Type::Int16: {
                const auto derivedColumn = static_cast_column_nullable<ColumnInt16>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int16_t *>(value)));
                break;
            }
            case Type::Int32: {
                const auto derivedColumn = static_cast_column_nullable<ColumnInt32>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int32_t *>(value)));
                break;
            }
            case Type::Int64: {
                const auto derivedColumn = static_cast_column_nullable<ColumnInt64>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int64_t *>(value)));
                break;
            }
            case Type::Int128: {
                const auto derivedColumn = static_cast_column_nullable<ColumnInt128>(column);
                const auto derivedValue = static_cast<const chc_int128 *>(value);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(absl::MakeInt128(derivedValue->high, derivedValue->low)));
                break;
            }
            case Type::UUID: {
                const auto derivedColumn = static_cast_column_nullable<ColumnUUID>(column);
                const auto derivedValue = static_cast<const chc_uuid *>(value);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(std::make_pair(derivedValue->first, derivedValue->second)));
                break;
            }
            case Type::Float32: {
                const auto derivedColumn = static_cast_column_nullable<ColumnFloat32>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const float *>(value)));
                break;
            }
            case Type::Float64: {
                const auto derivedColumn = static_cast_column_nullable<ColumnFloat64>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const double *>(value)));
                break;
            }
            case Type::Decimal: {
                const auto derivedColumn = static_cast_column_nullable<ColumnDecimal>(column);
                const auto derivedValue = static_cast<const chc_int128 *>(value);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(absl::MakeInt128(derivedValue->high, derivedValue->low)));
                break;
            }
            case Type::Date: {
                const auto derivedColumn = static_cast_column_nullable<ColumnDate>(column);
                derivedColumn->AppendRaw(value == nullptr
                                             ? std::nullopt
                                             : std::optional(*static_cast<const uint16_t *>(value)));
                break;
            }
            case Type::Date32: {
                const auto derivedColumn = static_cast_column_nullable<ColumnDate32>(column);
                derivedColumn->AppendRaw(value == nullptr
                                             ? std::nullopt
                                             : std::optional(*static_cast<const int32_t *>(value)));
                break;
            }
            case Type::DateTime: {
                const auto derivedColumn = static_cast_column_nullable<ColumnDateTime>(column);
                derivedColumn->AppendRaw(value == nullptr
                                             ? std::nullopt
                                             : std::optional(*static_cast<const uint32_t *>(value)));
                break;
            }
            case Type::DateTime64: {
                const auto derivedColumn = static_cast_column_nullable<ColumnDateTime64>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int64_t *>(value)));
                break;
            }
            case Type::Enum8: {
                const auto derivedColumn = static_cast_column_nullable<ColumnEnum8>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int8_t *>(value)));
                break;
            }
            case Type::Enum16: {
                const auto derivedColumn = static_cast_column_nullable<ColumnEnum16>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int16_t *>(value)));
                break;
            }
            case Type::String: {
                const auto derivedColumn = static_cast_column_nullable<ColumnString>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(static_cast<const char *>(value)));
                break;
            }
            case Type::FixedString: {
                const auto derivedColumn = static_cast_column_nullable<ColumnFixedString>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(static_cast<const char *>(value)));
                break;
            }
            case Type::IPv4: {
                const auto derivedColumn = static_cast_column_nullable<ColumnIPv4>(column);
                if (value == nullptr) {
                    derivedColumn->Append(std::nullopt);
                } else {
                    in_addr addr{};
                    addr.s_addr = *static_cast<const uint32_t *>(value);
                    derivedColumn->Append(std::optional(addr));
                }
                break;
            }
            case Type::IPv6: {
                const auto derivedColumn = static_cast_column_nullable<ColumnIPv6>(column);
                const auto derivedValue = static_cast<const unsigned char *>(value);
                if (value == nullptr) {
                    derivedColumn->Append(std::nullopt);
                } else {
                    in6_addr addr{};
                    for (int i = 0; i < 16; i++) {
                        addr.s6_addr[i] = derivedValue[i];
                    }
                    derivedColumn->Append(std::optional(addr));
                }
                break;
            }

            default:
                throw ValidationError(
                    std::string("Provided type is not supported for Nullable columns. Received ")
                    + nestedType->GetName() + "=" + std::to_string(nestedType->GetCode()));
        }
    });
}

extern "C" EXPORT inline void *chc_column_nullable_at(ColumnNullable *column, const size_t index) {
    const auto nestedType = column->Nested()->Type();

    switch (nestedType->GetCode()) {
        case Type::UInt8: {
            const auto value = static_cast_column_nullable<ColumnUInt8>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_uint8{true, value.value()}
                       : new chc_optional_uint8{false, 0};
        }
        case Type::UInt16: {
            const auto value = static_cast_column_nullable<ColumnUInt16>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_uint16{true, value.value()}
                       : new chc_optional_uint16{false, 0};
        }
        case Type::UInt32: {
            const auto value = static_cast_column_nullable<ColumnUInt32>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_uint32{true, value.value()}
                       : new chc_optional_uint32{false, 0};
        }
        case Type::UInt64: {
            const auto value = static_cast_column_nullable<ColumnUInt64>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_uint64{true, value.value()}
                       : new chc_optional_uint64{false, 0};
        }
        case Type::Int8: {
            const auto value = static_cast_column_nullable<ColumnInt8>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_int8{true, value.value()}
                       : new chc_optional_int8{false, 0};
        }
        case Type::Int16: {
            const auto value = static_cast_column_nullable<ColumnInt16>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_int16{true, value.value()}
                       : new chc_optional_int16{false, 0};
        }
        case Type::Int32: {
            const auto value = static_cast_column_nullable<ColumnInt32>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_int32{true, value.value()}
                       : new chc_optional_int32{false, 0};
        }
        case Type::Int64: {
            const auto value = static_cast_column_nullable<ColumnInt64>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_int64{true, value.value()}
                       : new chc_optional_int64{false, 0};
        }
        case Type::Int128: {
            const auto value = static_cast_column_nullable<ColumnInt128>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_int128{
                           true,
                           chc_int128{Int128High64(value.value()), Int128Low64(value.value())}
                       }
                       : new chc_optional_int128{false, 0, 0};
        }
        case Type::UUID: {
            const auto value = static_cast_column_nullable<ColumnUUID>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_uuid{true, value.value().first, value.value().second}
                       : new chc_optional_uuid{false, 0, 0};
        }
        case Type::Float32: {
            const auto value = static_cast_column_nullable<ColumnFloat32>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_float32{true, value.value()}
                       : new chc_optional_float32{false, 0};
        }
        case Type::Float64: {
            const auto value = static_cast_column_nullable<ColumnFloat64>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_float64{true, value.value()}
                       : new chc_optional_float64{false, 0};
        }
        case Type::Decimal: {
            const auto value = static_cast_column_nullable<ColumnDecimal>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_int128{
                           true,
                           chc_int128{Int128High64(value.value()), Int128Low64(value.value())}
                       }
                       : new chc_optional_int128{false, 0, 0};
        }
        case Type::Date: {
            const auto value = static_cast_column_nullable<ColumnDate>(column)->RawAt(index);
            return value.has_value()
                       ? new chc_optional_uint16{true, value.value()}
                       : new chc_optional_uint16{false, 0};
        }
        case Type::Date32: {
            const auto value = static_cast_column_nullable<ColumnDate32>(column)->RawAt(index);
            return value.has_value()
                       ? new chc_optional_int32{true, value.value()}
                       : new chc_optional_int32{false, 0};
        }
        case Type::DateTime: {
            const auto value = static_cast_column_nullable<ColumnDateTime>(column)->RawAt(index);
            return value.has_value()
                       ? new chc_optional_uint32{true, value.value()}
                       : new chc_optional_uint32{false, 0};
        }
        case Type::DateTime64: {
            const auto value = static_cast_column_nullable<ColumnDateTime64>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_int64{true, value.value()}
                       : new chc_optional_int64{false, 0};
        }
        case Type::Enum8: {
            const auto value = static_cast_column_nullable<ColumnEnum8>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_int8{true, value.value()}
                       : new chc_optional_int8{false, 0};
        }
        case Type::Enum16: {
            const auto value = static_cast_column_nullable<ColumnEnum16>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_int16{true, value.value()}
                       : new chc_optional_int16{false, 0};
        }
        case Type::String: {
            const auto value = static_cast_column_nullable<ColumnString>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_string_view{
                           true, chc_string_view{value.value().data(), value.value().length()}
                       }
                       : new chc_optional_string_view{false, chc_string_view{nullptr, 0}};
        }
        case Type::FixedString: {
            const auto value = static_cast_column_nullable<ColumnFixedString>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_string_view{
                           true, chc_string_view{value.value().data(), value.value().length()}
                       }
                       : new chc_optional_string_view{false, chc_string_view{nullptr, 0}};
        }
        case Type::IPv4: {
            const auto value = static_cast_column_nullable<ColumnIPv4>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_uint32{true, value.value().s_addr}
                       : new chc_optional_uint32{false, 0};
        }
        case Type::IPv6: {
            const auto value = static_cast_column_nullable<ColumnIPv6>(column)->At(index);
            return value.has_value()
                       ? new chc_optional_ipv6{true, value.value()}
                       : new chc_optional_ipv6{false, {}};
        }
        default:
            return nullptr;
    }
}
