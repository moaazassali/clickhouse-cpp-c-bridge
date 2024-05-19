#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt32 * CreateColumnInt32() {
	return new ColumnInt32();
}

extern "C" EXPORT inline void ColumnInt32Append(ColumnInt32 * column, const int32_t value) {
	column->Append(value);
}
