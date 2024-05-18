#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline ColumnInt32 * CreateColumnInt32() {
	return new ColumnInt32();
}

extern "C" __declspec(dllexport) inline void ColumnInt32Append(ColumnInt32 & column, int32_t value) {
	column.Append(value);
}
