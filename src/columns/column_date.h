#pragma once

#include <clickhouse/columns/date.h>
#include <clickhouse/columns/nullable.h>

#include "export.h"
#include "structs/optional_wrapper.h"

using namespace clickhouse;

extern "C" EXPORT inline ColumnDate *CreateColumnDate() {
    return new ColumnDate();
}

extern "C" EXPORT inline void ColumnDateAppendRaw(ColumnDate *column, const uint16_t value) {
    column->AppendRaw(value);
}

extern "C" EXPORT inline uint16_t ColumnDateRawAt(const ColumnDate *column, const size_t index) {
    return column->RawAt(index);
}
