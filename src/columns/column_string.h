#pragma once

#include <clickhouse/columns/string.h>
#include "structs/string_view_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnString *CreateColumnString() {
    return new ColumnString();
}

// Append(const char* str) creates a copy of the string, so you can free 'value' right after calling this function
extern "C" EXPORT inline void ColumnStringAppend(ColumnString *column, const char *value) {
    column->Append(value);
}

// Might add AppendNoManagedLifetime() in the future for better performance as it doesn't create a copy of the string
// but the caller must free each string when freeing the ColumnString as well

extern "C" EXPORT inline StringViewWrapper ColumnStringAt(const ColumnString *column, const size_t index) {
    auto sv = column->At(index);
    return {sv.data(), sv.length()};
}

// ==================================
// LowCardinality(String)
// ==================================
extern "C" EXPORT inline ColumnLowCardinalityT<ColumnString> *CreateColumnLowCardinality_String() {
    return new ColumnLowCardinalityT<ColumnString>();
}

extern "C" EXPORT inline void ColumnLowCardinality_String_Append(ColumnLowCardinalityT<ColumnString> *column,
                                                                 const char *value) {
    column->Append(value);
}

extern "C" EXPORT inline StringViewWrapper ColumnLowCardinality_String_At(
    const ColumnLowCardinalityT<ColumnString> *column,
    const size_t index) {
    auto sv = column->At(index);
    return {sv.data(), sv.length()};
}

// ==================================
// Nullable(String)
// ==================================
extern "C" EXPORT inline ColumnNullableT<ColumnString> *CreateColumnNullable_String() {
    return new ColumnNullableT<ColumnString>();
}

extern "C" EXPORT inline void ColumnNullable_String_Append(ColumnNullableT<ColumnString> *column, const char *value) {
    column->Append(value);
}

extern "C" EXPORT inline OptionalStringViewWrapper ColumnNullable_String_At(
    const ColumnNullableT<ColumnString> *column,
    const size_t index
) {
    const auto value = column->At(index);
    return value.has_value()
               ? OptionalStringViewWrapper{true, StringViewWrapper{value.value().data(), value.value().length()}}
               : OptionalStringViewWrapper{false, StringViewWrapper{nullptr, 0}};
}

// ==================================
// LowCardinality(Nullable(String))
// ==================================
extern "C" EXPORT inline ColumnLowCardinalityT<ColumnNullableT<ColumnString> > *
CreateColumnLowCardinality_Nullable_String() {
    return new ColumnLowCardinalityT<ColumnNullableT<ColumnString> >();
}

extern "C" EXPORT inline void ColumnLowCardinality_Nullable_String_Append(
    ColumnLowCardinalityT<ColumnNullableT<ColumnString> > *column,
    const char *value) {
    column->Append(value);
}

extern "C" EXPORT inline OptionalStringViewWrapper ColumnLowCardinality_Nullable_String_At(
    const ColumnLowCardinalityT<ColumnNullableT<ColumnString> > *column,
    const size_t index) {
    const auto value = column->At(index);
    return value.has_value()
               ? OptionalStringViewWrapper{true, StringViewWrapper{value.value().data(), value.value().length()}}
               : OptionalStringViewWrapper{false, StringViewWrapper{nullptr, 0}};
}
