#pragma once

#include <clickhouse/columns/array.h>
#include <clickhouse/types/types.h>

#include "export.h"
#include "utils.h"
#include "structs/clickhouse_result_status.h"

using namespace clickhouse;

// Like CreateColumnTuple(), we use a fake shared_ptr to give the external library full control over the columns.
extern "C" EXPORT inline chc_result_status chc_column_array_create(Column *inColumn, ColumnArray **outColumn) {
    return TryCatchClickHouseError([&]() {
        *outColumn = new ColumnArrayT(make_fake_shared(inColumn));
    });
}

extern "C" EXPORT inline int32_t chc_column_array_item_type(const ColumnArray *column) {
    return column->Type()->As<ArrayType>()->GetItemType()->GetCode();
}

// Wrapper to expose the protected methods of ColumnArray
class CustomColumnArray : public ColumnArray {
public:
    void AddOffsetCustom(const size_t offset) {
        AddOffset(offset);
    }

    size_t GetOffsetCustom(const size_t n) const {
        return GetOffset(n);
    }
};

// To append values to an array column of x depth:
// 1. Flatten the multi-dimensional array into a single array in row-major order
// 2. Append the flattened array to the innermost non-array column
// 3. Call ColumnArrayAddOffsets() on each nested array column to update the offsets
// The offsets are what "simulate" the multi-dimensional array structure
extern "C" EXPORT inline void chc_column_array_add_offset(ColumnArray *column, const size_t offset) {
    static_cast<CustomColumnArray *>(column)->AddOffsetCustom(offset);
}

extern "C" EXPORT inline size_t chc_column_array_get_offset(ColumnArray *column, const size_t n) {
    return static_cast<CustomColumnArray *>(column)->GetOffsetCustom(n);
}
