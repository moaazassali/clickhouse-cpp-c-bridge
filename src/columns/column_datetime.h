#pragma once

#include <clickhouse/columns/date.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline ColumnDateTime * CreateColumnDateTime() {
	return new ColumnDateTime();
}

extern "C" __declspec(dllexport) inline void ColumnDateTimeAppend(ColumnDateTime & column, const time_t & value) {
	column.Append(value);
}
