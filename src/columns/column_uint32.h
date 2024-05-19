#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnUInt32 * CreateColumnUInt32() {
	return new ColumnUInt32();
}

extern "C" EXPORT inline void ColumnUInt32Append(ColumnUInt32 * column, const uint32_t value) {
	column->Append(value);
}