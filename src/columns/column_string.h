#pragma once

#include <clickhouse/columns/string.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline ColumnString * CreateColumnString() {
	return new ColumnString();
}

extern "C" __declspec(dllexport) inline void ColumnStringAppend(ColumnString & column, const char* value) {
	column.Append(value);
}
