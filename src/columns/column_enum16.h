#pragma once

using namespace clickhouse;

extern "C" EXPORT inline ColumnEnum16 *CreateColumnEnum16() {
    return new ColumnEnum16({});
}

extern "C" EXPORT inline void ColumnEnum16Append(ColumnEnum16 *column, const int16_t value) {
    column->Append(value);
}

extern "C" EXPORT inline int16_t ColumnEnum16At(const ColumnEnum16 *column, const size_t index) {
    return column->At(index);
}
