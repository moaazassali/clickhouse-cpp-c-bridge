#pragma once

#include <clickhouse/columns/numeric.h>

using namespace clickhouse;

extern "C" EXPORT inline ColumnFloat32 * CreateColumnFloat32() {
	return new ColumnFloat32();
}

extern "C" EXPORT inline void ColumnFloat32Append(ColumnFloat32 * column, const float value) {
	column->Append(value);
}
