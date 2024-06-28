#pragma once
#include "clickhouse/columns/column.h"

using namespace clickhouse;

template<typename T>
std::shared_ptr<T> make_fake_shared(T *ptr) {
    return std::shared_ptr<T>(ptr, [](T *) {
    });
}

/// Downcast raw pointer to the specific column's subtype as a raw pointer.
// This is an alternative to column->AsStrict<>() so we can get a raw pointer instead of a shared_ptr.
template<typename T>
inline T *AsStrict(Column *column) {
    auto result = dynamic_cast<T *>(column);
    if (!result) {
        throw ValidationError(
            "dynamic_cast failed. Casting type does not match the provided column's type. Expected column "
            + std::string(typeid(T).name()) + " but got " + column->Type()->GetName());
    }
    return result;
}
