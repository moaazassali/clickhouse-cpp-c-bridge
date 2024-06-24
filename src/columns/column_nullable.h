#pragma once

/*
 * This file only includes common functions for nullable columns.
 * Refer to each column type that supports Nullable for specific functions.
 */

template<typename T>
inline void ColumnNullableAppendNull(ColumnNullableT<T> *column) {
    column->Append(std::nullopt);
}
