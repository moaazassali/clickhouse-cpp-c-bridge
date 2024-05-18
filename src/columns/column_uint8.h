#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline ColumnUInt8 * CreateColumnUInt8() {
	return new ColumnUInt8();
}

extern "C" __declspec(dllexport) inline void ColumnUInt8Append(ColumnUInt8 & column, uint8_t value) {
	column.Append(value);
}