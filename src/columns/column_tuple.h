#pragma once

#include <cstdarg>
#include <clickhouse/columns/tuple.h>

#include "export.h"
#include "utils.h"
#include "structs/clickhouse_result_status.h"

using namespace clickhouse;

// We use a fake shared_ptr to give the external library full control over the columns.
// However, these columns should probably not be directly exposed to the end user.
// Instead, the library should create them based on the passed types by the user and only expose ColumnTuple.
// But there might be a use case for exposing the columns, so we won't limit the functionality here.
extern "C" EXPORT inline chc_result_status chc_column_tuple_create(ColumnTuple **outColumn, int n, ...) {
    va_list args;
    va_start(args, n);

    return TryCatchClickHouseError([&]() {
        if (n <= 0) {
            throw ValidationError("Tuple size should be greater than 0");
        }

        std::vector<ColumnRef> columns;

        for (int i = 0; i < n; ++i) {
            Column *col = va_arg(args, Column*);
            if (col == nullptr) {
                throw ValidationError("Argument " + std::to_string(i + 3) + " is nullptr, not a valid column pointer");
            }
            columns.push_back(make_fake_shared(col));
        }

        va_end(args);

        *outColumn = new ColumnTuple(columns);
    });
}

extern "C" EXPORT inline Column *chc_column_tuple_column_at(const ColumnTuple *column, const size_t index) {
    return column->At(index).get();
}

extern "C" EXPORT inline size_t chc_column_tuple_column_count(const ColumnTuple *column) {
    return column->TupleSize();
}
