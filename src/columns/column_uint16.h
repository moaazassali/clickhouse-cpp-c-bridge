#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline ColumnUInt16 * CreateColumnUInt16() {
	return new ColumnUInt16();
}

extern "C" __declspec(dllexport) inline void ColumnUInt16Append(ColumnUInt16 & column, uint16_t value) {
	column.Append(value);
}