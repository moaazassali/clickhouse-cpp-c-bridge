#pragma once

#include <clickhouse/columns/date.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnDateTime * CreateColumnDateTime() {
	return new ColumnDateTime();
}

extern "C" EXPORT inline void ColumnDateTimeAppend(ColumnDateTime * column, const uint32_t value) {
	column->Append(value);
}

extern "C" EXPORT inline uint32_t ColumnDateTimeAt(const ColumnDateTime * column, const size_t index) {
	return column->At(index);
}
