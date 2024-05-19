#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt64 * CreateColumnInt64() {
	return new ColumnInt64();
}

extern "C" EXPORT inline void ColumnInt64Append(ColumnInt64 * column, const int64_t value) {
	column->Append(value);
}
