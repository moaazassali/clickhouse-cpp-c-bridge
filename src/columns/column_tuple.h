#pragma once

using namespace clickhouse;

// We use a fake shared_ptr to give the external library full control over the columns.
// However, these columns should probably not be directly exposed to the end user.
// Instead, the library should create them based on the passed types by the user and only expose ColumnTuple.
// But there might be a use case for exposing the columns, so we won't limit the functionality here.
extern "C" EXPORT inline ColumnTuple *CreateColumnTuple(int n, ...) {
    std::vector<ColumnRef> columns;
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; ++i) {
        Column *col = va_arg(args, Column*);
        columns.push_back(make_fake_shared(col));
    }

    va_end(args);

    return new ColumnTuple(columns);
}

extern "C" EXPORT inline Column *ColumnTupleColumnAt(const ColumnTuple *column, const size_t index) {
    return column->At(index).get();
}

extern "C" EXPORT inline size_t ColumnTupleColumnCount(const ColumnTuple *column) {
    return column->TupleSize();
}
