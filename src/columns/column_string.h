#pragma once

#include <clickhouse/columns/string.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnString * CreateColumnString() {
	return new ColumnString();
}

extern "C" EXPORT inline void ColumnStringAppend(ColumnString * column, const char* value) {
	column->Append(value);
}

extern "C" EXPORT inline const char* ColumnStringAt(const ColumnString * column, const size_t index) {
	return column->At(index).data();
}
