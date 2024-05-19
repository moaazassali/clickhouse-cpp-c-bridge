#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnInt16 * CreateColumnInt16() {
	return new ColumnInt16();
}

extern "C" EXPORT inline void ColumnInt16Append(ColumnInt16 * column, const int16_t value) {
	column->Append(value);
}