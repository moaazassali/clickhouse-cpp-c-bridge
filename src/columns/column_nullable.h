#pragma once

/*
 * This file only includes common functions for nullable columns.
 * Refer to each column type that supports Nullable for specific functions.
 */

template<typename T>
inline void ColumnNullableAppendNull(ColumnNullableT<T> *column) {
    column->Append(std::nullopt);
}

// For FixedString and Decimal, pass length/precision as a
// For DateTime64, pass precision and scale as a and b respectively
// For all other types, a and b does not have any effect, pass whatever you want
extern "C" EXPORT inline ClickHouseResultStatus CreateColumnNullable(const Type::Code code, const size_t a,
                                                                     const size_t b, Column **column) {
    return TryCatchClickHouseError([&]() {
        switch (code) {
            case Type::UInt8:
                *column = new ColumnNullableT<ColumnUInt8>();
                break;
            case Type::UInt16:
                *column = new ColumnNullableT<ColumnUInt16>();
                break;
            case Type::UInt32:
                *column = new ColumnNullableT<ColumnUInt32>();
                break;
            case Type::UInt64:
                *column = new ColumnNullableT<ColumnUInt64>();
                break;
            case Type::Int8:
                *column = new ColumnNullableT<ColumnInt8>();
                break;
            case Type::Int16:
                *column = new ColumnNullableT<ColumnInt16>();
                break;
            case Type::Int32:
                *column = new ColumnNullableT<ColumnInt32>();
                break;
            case Type::Int64:
                *column = new ColumnNullableT<ColumnInt64>();
                break;
            case Type::Int128:
                *column = new ColumnNullableT<ColumnInt128>();
                break;
            case Type::UUID:
                *column = new ColumnNullableT<ColumnUUID>();
                break;
            case Type::Float32:
                *column = new ColumnNullableT<ColumnFloat32>();
                break;
            case Type::Float64:
                *column = new ColumnNullableT<ColumnFloat64>();
                break;
            case Type::Decimal:
                *column = new ColumnNullableT<ColumnDecimal>(a, b);
                break;
            case Type::Date:
                *column = new ColumnNullableT<ColumnDate>();
                break;
            case Type::Date32:
                *column = new ColumnNullableT<ColumnDate32>();
                break;
            case Type::DateTime:
                *column = new ColumnNullableT<ColumnDateTime>();
                break;
            case Type::DateTime64:
                *column = new ColumnNullableT<ColumnDateTime64>(a);
                break;
            case Type::Enum8:
                *column = new ColumnNullableT<ColumnEnum8>(Type::CreateEnum8({}));
                break;
            case Type::Enum16:
                *column = new ColumnNullableT<ColumnEnum16>(Type::CreateEnum8({}));
                break;
            case Type::String:
                *column = new ColumnNullableT<ColumnString>();
                break;
            case Type::FixedString:
                *column = new ColumnNullableT<ColumnFixedString>(a);
                break;
            case Type::IPv4:
                *column = new ColumnNullableT<ColumnIPv4>();
                break;
            case Type::IPv6:
                *column = new ColumnNullableT<ColumnIPv6>();
                break;

            default:
                throw ValidationError(
                    std::string("Provided type is not supported for Nullable columns: ") +
                    Type::TypeName(code) + "=" + std::to_string(code));
        }
    });
}

template<typename T>
ColumnNullableT<T> *dynamic_cast_column_nullable(ColumnNullable *column) {
    auto result = dynamic_cast<ColumnNullableT<T> *>(column);
    if (result == nullptr) {
        throw ValidationError(
            "dynamic_cast failed. Most likely caused by column type mismatch. Expected nested column "
            + std::string(typeid(T).name()) + " but got " + column->Nested()->GetType().GetName());
    }
    return result;
}

// Pass nullptr to append a NULL value
extern "C" EXPORT inline ClickHouseResultStatus ColumnNullableAppend(ColumnNullable *column, const void *value) {
    return TryCatchClickHouseError([&]() {
        if (const auto columnType = column->Type(); columnType->GetCode() != Type::Nullable) {
            throw ValidationError(
                std::string("Provided column is not Nullable. Received ") + columnType->GetName()
                + "=" + std::to_string(columnType->GetCode()));
        }

        const auto nestedType = column->Nested()->Type();

        switch (nestedType->GetCode()) {
            case Type::UInt8: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnUInt8>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const uint8_t *>(value)));
                break;
            }
            case Type::UInt16: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnUInt16>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const uint16_t *>(value)));
                break;
            }
            case Type::UInt32: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnUInt32>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const uint32_t *>(value)));
                break;
            }
            case Type::UInt64: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnUInt64>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const uint64_t *>(value)));
                break;
            }
            case Type::Int8: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnInt8>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int8_t *>(value)));
                break;
            }
            case Type::Int16: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnInt16>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int16_t *>(value)));
                break;
            }
            case Type::Int32: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnInt32>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int32_t *>(value)));
                break;
            }
            case Type::Int64: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnInt64>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int64_t *>(value)));
                break;
            }
            case Type::Int128: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnInt128>(column);
                const auto derivedValue = static_cast<const Int128Wrapper *>(value);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(absl::MakeInt128(derivedValue->high, derivedValue->low)));
                break;
            }
            case Type::UUID: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnUUID>(column);
                const auto derivedValue = static_cast<const UUIDWrapper *>(value);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(std::make_pair(derivedValue->first, derivedValue->second)));
                break;
            }
            case Type::Float32: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnFloat32>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const float *>(value)));
                break;
            }
            case Type::Float64: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnFloat64>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const double *>(value)));
                break;
            }
            case Type::Decimal: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnDecimal>(column);
                const auto derivedValue = static_cast<const Int128Wrapper *>(value);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(absl::MakeInt128(derivedValue->high, derivedValue->low)));
                break;
            }
            case Type::Date: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnDate>(column);
                derivedColumn->AppendRaw(value == nullptr
                                             ? std::nullopt
                                             : std::optional(*static_cast<const uint16_t *>(value)));
                break;
            }
            case Type::Date32: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnDate32>(column);
                derivedColumn->AppendRaw(value == nullptr
                                             ? std::nullopt
                                             : std::optional(*static_cast<const int32_t *>(value)));
                break;
            }
            case Type::DateTime: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnDateTime>(column);
                derivedColumn->AppendRaw(value == nullptr
                                             ? std::nullopt
                                             : std::optional(*static_cast<const uint32_t *>(value)));
                break;
            }
            case Type::DateTime64: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnDateTime64>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int64_t *>(value)));
                break;
            }
            case Type::Enum8: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnEnum8>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int8_t *>(value)));
                break;
            }
            case Type::Enum16: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnEnum16>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(*static_cast<const int16_t *>(value)));
                break;
            }
            case Type::String: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnString>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(static_cast<const char *>(value)));
                break;
            }
            case Type::FixedString: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnFixedString>(column);
                derivedColumn->Append(value == nullptr
                                          ? std::nullopt
                                          : std::optional(static_cast<const char *>(value)));
                break;
            }
            case Type::IPv4: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnIPv4>(column);
                in_addr addr{};
                addr.s_addr = *static_cast<const uint32_t *>(value);
                derivedColumn->Append(value == nullptr ? std::nullopt : std::optional(addr));
                break;
            }
            case Type::IPv6: {
                const auto derivedColumn = dynamic_cast_column_nullable<ColumnIPv6>(column);
                const auto derivedValue = static_cast<const unsigned char *>(value);
                in6_addr addr{};
                for (int i = 0; i < 16; i++) {
                    addr.s6_addr[i] = derivedValue[i];
                }
                derivedColumn->Append(value == nullptr ? std::nullopt : std::optional(addr));
                break;
            }

            default:
                throw ValidationError(
                    std::string("Provided type is not supported for Nullable columns. Received ")
                    + nestedType->GetName() + "=" + std::to_string(nestedType->GetCode()));
        }
    });
}

extern "C" EXPORT inline void *ColumnNullableAt(ColumnNullable *column, const size_t index) {
    const auto nestedType = column->Nested()->Type();

    switch (nestedType->GetCode()) {
        case Type::UInt8: {
            const auto value = dynamic_cast_column_nullable<ColumnUInt8>(column)->At(index);
            return value.has_value()
                       ? new OptionalUInt8Wrapper{true, value.value()}
                       : new OptionalUInt8Wrapper{false, 0};
        }
        case Type::UInt16: {
            const auto value = dynamic_cast_column_nullable<ColumnUInt16>(column)->At(index);
            return value.has_value()
                       ? new OptionalUInt16Wrapper{true, value.value()}
                       : new OptionalUInt16Wrapper{false, 0};
        }
        case Type::UInt32: {
            const auto value = dynamic_cast_column_nullable<ColumnUInt32>(column)->At(index);
            return value.has_value()
                       ? new OptionalUInt32Wrapper{true, value.value()}
                       : new OptionalUInt32Wrapper{false, 0};
        }
        case Type::UInt64: {
            const auto value = dynamic_cast_column_nullable<ColumnUInt64>(column)->At(index);
            return value.has_value()
                       ? new OptionalUInt64Wrapper{true, value.value()}
                       : new OptionalUInt64Wrapper{false, 0};
        }
        case Type::Int8: {
            const auto value = dynamic_cast_column_nullable<ColumnInt8>(column)->At(index);
            return value.has_value()
                       ? new OptionalInt8Wrapper{true, value.value()}
                       : new OptionalInt8Wrapper{false, 0};
        }
        case Type::Int16: {
            const auto value = dynamic_cast_column_nullable<ColumnInt16>(column)->At(index);
            return value.has_value()
                       ? new OptionalInt16Wrapper{true, value.value()}
                       : new OptionalInt16Wrapper{false, 0};
        }
        case Type::Int32: {
            const auto value = dynamic_cast_column_nullable<ColumnInt32>(column)->At(index);
            return value.has_value()
                       ? new OptionalInt32Wrapper{true, value.value()}
                       : new OptionalInt32Wrapper{false, 0};
        }
        case Type::Int64: {
            const auto value = dynamic_cast_column_nullable<ColumnInt64>(column)->At(index);
            return value.has_value()
                       ? new OptionalInt64Wrapper{true, value.value()}
                       : new OptionalInt64Wrapper{false, 0};
        }
        case Type::Int128: {
            const auto value = dynamic_cast_column_nullable<ColumnInt128>(column)->At(index);
            return value.has_value()
                       ? new OptionalInt128Wrapper{
                           true,
                           Int128Wrapper{Int128High64(value.value()), Int128Low64(value.value())}
                       }
                       : new OptionalInt128Wrapper{false, 0, 0};
        }
        case Type::UUID: {
            const auto value = dynamic_cast_column_nullable<ColumnUUID>(column)->At(index);
            return value.has_value()
                       ? new OptionalUUIDWrapper{true, value.value().first, value.value().second}
                       : new OptionalUUIDWrapper{false, 0, 0};
        }
        case Type::Float32: {
            const auto value = dynamic_cast_column_nullable<ColumnFloat32>(column)->At(index);
            return value.has_value()
                       ? new OptionalFloat32Wrapper{true, value.value()}
                       : new OptionalFloat32Wrapper{false, 0};
        }
        case Type::Float64: {
            const auto value = dynamic_cast_column_nullable<ColumnFloat64>(column)->At(index);
            return value.has_value()
                       ? new OptionalFloat64Wrapper{true, value.value()}
                       : new OptionalFloat64Wrapper{false, 0};
        }
        case Type::Decimal: {
            const auto value = dynamic_cast_column_nullable<ColumnDecimal>(column)->At(index);
            return value.has_value()
                       ? new OptionalInt128Wrapper{
                           true,
                           Int128Wrapper{Int128High64(value.value()), Int128Low64(value.value())}
                       }
                       : new OptionalInt128Wrapper{false, 0, 0};
        }
        case Type::Date: {
            const auto value = dynamic_cast_column_nullable<ColumnDate>(column)->RawAt(index);
            return value.has_value()
                       ? new OptionalUInt16Wrapper{true, value.value()}
                       : new OptionalUInt16Wrapper{false, 0};
        }
        case Type::Date32: {
            const auto value = dynamic_cast_column_nullable<ColumnDate32>(column)->RawAt(index);
            return value.has_value()
                       ? new OptionalInt32Wrapper{true, value.value()}
                       : new OptionalInt32Wrapper{false, 0};
        }
        case Type::DateTime: {
            const auto value = dynamic_cast_column_nullable<ColumnDateTime>(column)->RawAt(index);
            return value.has_value()
                       ? new OptionalUInt32Wrapper{true, value.value()}
                       : new OptionalUInt32Wrapper{false, 0};
        }
        case Type::DateTime64: {
            const auto value = dynamic_cast_column_nullable<ColumnDateTime64>(column)->At(index);
            return value.has_value()
                       ? new OptionalInt64Wrapper{true, value.value()}
                       : new OptionalInt64Wrapper{false, 0};
        }
        case Type::Enum8: {
            const auto value = dynamic_cast_column_nullable<ColumnEnum8>(column)->At(index);
            return value.has_value()
                       ? new OptionalInt8Wrapper{true, value.value()}
                       : new OptionalInt8Wrapper{false, 0};
        }
        case Type::Enum16: {
            const auto value = dynamic_cast_column_nullable<ColumnEnum16>(column)->At(index);
            return value.has_value()
                       ? new OptionalInt16Wrapper{true, value.value()}
                       : new OptionalInt16Wrapper{false, 0};
        }
        case Type::String: {
            const auto value = dynamic_cast_column_nullable<ColumnString>(column)->At(index);
            return value.has_value()
                       ? new OptionalStringViewWrapper{
                           true, StringViewWrapper{value.value().data(), value.value().length()}
                       }
                       : new OptionalStringViewWrapper{false, StringViewWrapper{nullptr, 0}};
        }
        case Type::FixedString: {
            const auto value = dynamic_cast_column_nullable<ColumnFixedString>(column)->At(index);
            return value.has_value()
                       ? new OptionalStringViewWrapper{
                           true, StringViewWrapper{value.value().data(), value.value().length()}
                       }
                       : new OptionalStringViewWrapper{false, StringViewWrapper{nullptr, 0}};
        }
        case Type::IPv4: {
            const auto value = dynamic_cast_column_nullable<ColumnIPv4>(column)->At(index);
            return value.has_value()
                       ? new OptionalUInt32Wrapper{true, value.value().s_addr}
                       : new OptionalUInt32Wrapper{false, 0};
        }
        case Type::IPv6: {
            const auto value = dynamic_cast_column_nullable<ColumnIPv6>(column)->At(index);
            return value.has_value()
                       ? new OptionalIPv6Wrapper{true, value.value().s6_addr}
                       : new OptionalIPv6Wrapper{false, nullptr};
        }
        default:
            return nullptr;
    }
}
