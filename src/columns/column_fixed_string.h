#pragma once

using namespace clickhouse;

extern "C" EXPORT inline ColumnFixedString *CreateColumnFixedString(const size_t n) {
    return new ColumnFixedString(n);
}

// Append(const char* str) creates a copy of the string, so you can free 'value' right after calling this function
extern "C" EXPORT inline ClickHouseResultStatus ColumnFixedStringAppend(ColumnFixedString *column, const char *value) {
    return TryCatchClickHouseError([&]() {
        column->Append(value);
    });
}

extern "C" EXPORT inline StringViewWrapper ColumnFixedStringAt(const ColumnFixedString *column, const size_t index) {
    auto sv = column->At(index);
    return {sv.data(), sv.length()};
}

// ========================================
// LowCardinality(FixedString)
// ========================================
extern "C" EXPORT inline ColumnLowCardinalityT<ColumnFixedString> *
CreateColumnLowCardinality_FixedString(const size_t n) {
    return new ColumnLowCardinalityT<ColumnFixedString>(n);
}

extern "C" EXPORT inline ClickHouseResultStatus ColumnLowCardinality_FixedString_Append(
    ColumnLowCardinalityT<ColumnFixedString> *column,
    const char *value) {
    return TryCatchClickHouseError([&]() {
        column->Append(value);
    });
}

extern "C" EXPORT inline StringViewWrapper ColumnLowCardinality_FixedString_At(
    const ColumnLowCardinalityT<ColumnFixedString> *column,
    const size_t index) {
    auto sv = column->At(index);
    return {sv.data(), sv.length()};
}
