#pragma once

#include <clickhouse/columns/date.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline ColumnDateTime64 * CreateColumnDateTime64(const size_t precision) {
	return new ColumnDateTime64(precision);
}

extern "C" __declspec(dllexport) inline void ColumnDateTime64Append(ColumnDateTime64 & column, const int64_t & value) {
	column.Append(value);
}