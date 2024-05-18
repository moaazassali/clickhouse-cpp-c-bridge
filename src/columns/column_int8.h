#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline ColumnInt8 * CreateColumnInt8() {
	return new ColumnInt8();
}

extern "C" __declspec(dllexport) inline void ColumnInt8Append(ColumnInt8 & column, int8_t value) {
	column.Append(value);
}
