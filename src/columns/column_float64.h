#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline ColumnFloat64 * CreateColumnFloat64() {
	return new ColumnFloat64();
}

extern "C" __declspec(dllexport) inline void ColumnFloat64Append(ColumnFloat64 * column, const double value) {
	column->Append(value);
}