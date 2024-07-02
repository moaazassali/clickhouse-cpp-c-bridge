#pragma once

#include <clickhouse/columns/numeric.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnFloat32 *CreateColumnFloat32() {
    return new ColumnFloat32();
}

extern "C" EXPORT inline void ColumnFloat32Append(ColumnFloat32 *column, const float value) {
    column->Append(value);
}

extern "C" EXPORT inline float ColumnFloat32At(const ColumnFloat32 *column, const size_t index) {
    return column->At(index);
}
