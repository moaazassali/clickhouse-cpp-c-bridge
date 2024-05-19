#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnUInt8 * CreateColumnUInt8() {
	return new ColumnUInt8();
}

extern "C" EXPORT inline void ColumnUInt8Append(ColumnUInt8 * column, const uint8_t value) {
	column->Append(value);
}