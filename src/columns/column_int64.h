#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline ColumnInt64 * CreateColumnInt64() {
	return new ColumnInt64();
}

extern "C" __declspec(dllexport) inline void ColumnInt64Append(ColumnInt64 * column, const int64_t value) {
	column->Append(value);
}
