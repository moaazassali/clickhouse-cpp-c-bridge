#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt32 * CreateColumnInt32() {
	return new ColumnInt32();
}

extern "C" EXPORT inline void ColumnInt32Append(ColumnInt32 * column, const int32_t value) {
	column->Append(value);
}

extern "C" EXPORT inline int32_t ColumnInt32At(const ColumnInt32 * column, const size_t index) {
	return column->At(index);
}
