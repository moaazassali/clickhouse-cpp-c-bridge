#pragma once

using namespace clickhouse;

extern "C" EXPORT inline ColumnTuple *CreateColumnTuple(int n, ...) {
    std::vector<ColumnRef> columns;
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; ++i) {
        Column *col = va_arg(args, Column*);
        // fake shared_ptr to comply with the method signature
        const std::shared_ptr<Column> colSharedPtr(col, [](Column *) {
        });
        columns.push_back(colSharedPtr);
    }

    va_end(args);

    return new ColumnTuple(columns);
}

extern "C" EXPORT inline Column *ColumnTupleAt(const ColumnTuple *column, const size_t index) {
    return column->At(index).get();
}

extern "C" EXPORT inline size_t ColumnTupleSize(const ColumnTuple *column) {
    return column->TupleSize();
}
