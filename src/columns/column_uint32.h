#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" __declspec(dllexport) inline ColumnUInt32 * CreateColumnUInt32() {
	return new ColumnUInt32();
}

extern "C" __declspec(dllexport) inline void ColumnUInt32Append(ColumnUInt32 * column, const uint32_t value) {
	column->Append(value);
}