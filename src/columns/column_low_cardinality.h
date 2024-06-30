#pragma once

#include <clickhouse/columns/lowcardinality.h>
#include <clickhouse/columns/string.h>

#include "export.h"
#include "utils.h"
#include "structs/optional_wrapper.h"
#include "structs/clickhouse_result_status.h"

using namespace clickhouse;

// Uses inColumn to create a new copy of it, so calling this function with a large non-empty inColumn is expensive.
// inColumn should be freed after calling this method.
extern "C" EXPORT inline ClickHouseResultStatus CreateColumnLowCardinality(Column *inColumn, Column **outColumn) {
    return TryCatchClickHouseError([&]() {
        const auto type = inColumn->Type();

        switch (type->GetCode()) {
            case Type::String:
                *outColumn = new ColumnLowCardinalityT(make_fake_shared(static_cast<ColumnString *>(inColumn)));
                return;
            case Type::FixedString:
                *outColumn = new ColumnLowCardinalityT(make_fake_shared(static_cast<ColumnFixedString *>(inColumn)));
                return;
            case Type::Nullable: {
                const auto nullableType = type->As<NullableType>()->GetNestedType();

                switch (nullableType->GetCode()) {
                    case Type::String:
                        *outColumn = new ColumnLowCardinalityT(
                            make_fake_shared(static_cast<ColumnNullableT<ColumnString> *>(inColumn)));
                        return;
                    case Type::FixedString:
                        *outColumn = new ColumnLowCardinalityT(
                            make_fake_shared(static_cast<ColumnNullableT<ColumnFixedString> *>(inColumn)));
                        return;
                    default:
                        throw ValidationError(
                            "Unsupported nested type for low cardinality column: " + nullableType->GetName());
                }
            }
            default:
                throw ValidationError("Unsupported nested type for low cardinality column: " + type->GetName());
        }
    });
}

// For nullable columns ONLY, you can pass nullptr to append a NULL value.
extern "C" EXPORT inline ClickHouseResultStatus ColumnLowCardinalityAppend(
    ColumnLowCardinality *column, const void *value) {
    return TryCatchClickHouseError([&]() {
        const auto nestedType = column->GetNestedType();

        switch (nestedType->GetCode()) {
            case Type::String: {
                const auto derivedColumn = static_cast<ColumnLowCardinalityT<ColumnString> *>(column);
                derivedColumn->Append(static_cast<const char *>(value));
                return;
            }
            case Type::FixedString: {
                const auto derivedColumn = static_cast<ColumnLowCardinalityT<ColumnFixedString> *>(column);
                derivedColumn->Append(static_cast<const char *>(value));
                return;
            }
            case Type::Nullable: {
                const auto nullableType = nestedType->As<NullableType>()->GetNestedType();

                switch (nullableType->GetCode()) {
                    case Type::String: {
                        const auto derivedColumn = static_cast<ColumnLowCardinalityT<ColumnNullableT<ColumnString> > *>(
                            column);
                        derivedColumn->Append((value == nullptr
                                                   ? std::nullopt
                                                   : std::optional(static_cast<const char *>(value))));
                        return;
                    }
                    case Type::FixedString: {
                        const auto derivedColumn = static_cast<ColumnLowCardinalityT<ColumnNullableT<
                            ColumnFixedString> > *>(column);
                        derivedColumn->Append((value == nullptr
                                                   ? std::nullopt
                                                   : std::optional(static_cast<const char *>(value))));
                        return;
                    }
                    default:
                        throw ValidationError(
                            "Unsupported nested type for low cardinality column: " + nullableType->GetName());
                }
            }
            default:
                throw ValidationError("Unsupported nested type for low cardinality column: " + nestedType->GetName());
        }
    });
}

extern "C" EXPORT inline void *ColumnLowCardinalityAt(ColumnLowCardinality *column, const size_t index) {
    const auto nestedType = column->GetNestedType();

    switch (nestedType->GetCode()) {
        case Type::String: {
            const auto value = static_cast<ColumnLowCardinalityT<ColumnString> *>(column)->At(index);
            return new StringViewWrapper{value.data(), value.length()};
        }
        case Type::FixedString: {
            const auto value = static_cast<ColumnLowCardinalityT<ColumnFixedString> *>(column)->At(index);
            return new StringViewWrapper{value.data(), value.length()};
        }
        case Type::Nullable: {
            const auto nullableType = nestedType->As<NullableType>()->GetNestedType();

            switch (nullableType->GetCode()) {
                case Type::String: {
                    const auto value = static_cast<ColumnLowCardinalityT<ColumnNullableT<ColumnString> > *>(column)->
                            At(index);
                    return value.has_value()
                               ? new OptionalStringViewWrapper{
                                   true, StringViewWrapper{value.value().data(), value.value().length()}
                               }
                               : new OptionalStringViewWrapper{false, StringViewWrapper{nullptr, 0}};
                }
                case Type::FixedString: {
                    const auto value = static_cast<ColumnLowCardinalityT<ColumnNullableT<ColumnFixedString> > *>(column)->
                            At(index);
                    return value.has_value()
                               ? new OptionalStringViewWrapper{
                                   true, StringViewWrapper{value.value().data(), value.value().length()}
                               }
                               : new OptionalStringViewWrapper{false, StringViewWrapper{nullptr, 0}};
                }
                default: return nullptr;
            }
        }
        default: return nullptr;
    }
}
