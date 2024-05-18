#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline ColumnInt16 * CreateColumnInt16() {
	return new ColumnInt16();
}

extern "C" __declspec(dllexport) inline void ColumnInt16Append(ColumnInt16 & column, int16_t value) {
	column.Append(value);
}