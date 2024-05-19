#pragma once

#include <clickhouse/columns/date.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnDateTime * CreateColumnDateTime() {
	return new ColumnDateTime();
}

extern "C" EXPORT inline void ColumnDateTimeAppend(ColumnDateTime * column, const time_t value) {
	column->Append(value);
}
