#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt8 * CreateColumnInt8() {
	return new ColumnInt8();
}

extern "C" EXPORT inline void ColumnInt8Append(ColumnInt8 * column, const int8_t value) {
	column->Append(value);
}
