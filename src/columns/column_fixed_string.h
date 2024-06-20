#pragma once

using namespace clickhouse;

extern "C" EXPORT inline ColumnFixedString *CreateColumnFixedString(const size_t n) {
    return new ColumnFixedString(n);
}

extern "C" EXPORT inline ClickHouseResultStatus ColumnFixedStringAppend(ColumnFixedString *column, const char *value) {
    return TryCatchClickHouseError([&]() {
        column->Append(value);
    });
}

extern "C" EXPORT inline StringViewWrapper ColumnFixedStringAt(const ColumnFixedString *column, const size_t index) {
    auto sv = column->At(index);
    return {sv.data(), sv.length()};
}
