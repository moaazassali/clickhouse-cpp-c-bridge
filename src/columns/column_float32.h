#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline ColumnFloat32 * CreateColumnFloat32() {
	return new ColumnFloat32();
}

extern "C" __declspec(dllexport) inline void ColumnFloat32Append(ColumnFloat32 & column, float value) {
	column.Append(value);
}
