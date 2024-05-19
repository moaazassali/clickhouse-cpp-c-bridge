#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnUInt16 * CreateColumnUInt16() {
	return new ColumnUInt16();
}

extern "C" EXPORT inline void ColumnUInt16Append(ColumnUInt16 * column, const uint16_t value) {
	column->Append(value);
}