#pragma once

#include <clickhouse/types/types.h>

#include "structs/int128_wrapper.h"
#include "structs/string_view_wrapper.h"
#include "structs/uuid_wrapper.h"
#include "export.h"
#include "clickhouse/base/socket.h"

using namespace clickhouse;

#define OptionalWrapper(type, name) struct { bool has_value; type value; } name;


typedef OptionalWrapper(StringViewWrapper, OptionalStringViewWrapper);

typedef OptionalWrapper(int8_t, OptionalInt8Wrapper);

typedef OptionalWrapper(int16_t, OptionalInt16Wrapper);

typedef OptionalWrapper(int32_t, OptionalInt32Wrapper);

typedef OptionalWrapper(int64_t, OptionalInt64Wrapper);

typedef OptionalWrapper(Int128Wrapper, OptionalInt128Wrapper);

typedef OptionalWrapper(uint8_t, OptionalUInt8Wrapper);

typedef OptionalWrapper(uint16_t, OptionalUInt16Wrapper);

typedef OptionalWrapper(uint32_t, OptionalUInt32Wrapper);

typedef OptionalWrapper(uint64_t, OptionalUInt64Wrapper);

typedef OptionalWrapper(float, OptionalFloat32Wrapper);

typedef OptionalWrapper(double, OptionalFloat64Wrapper);

typedef OptionalWrapper(UUIDWrapper, OptionalUUIDWrapper);

struct OptionalIPv6Wrapper {
    bool has_value;
    in6_addr value;
};

extern "C" EXPORT inline void FreeOptionalWrapper(const void *wrapper, const Type::Code code) {
    switch (code) {
        case Type::UInt8:
            delete static_cast<const OptionalUInt8Wrapper *>(wrapper);
            break;
        case Type::UInt16:
            delete static_cast<const OptionalUInt16Wrapper *>(wrapper);
            break;
        case Type::UInt32:
            delete static_cast<const OptionalUInt32Wrapper *>(wrapper);
            break;
        case Type::UInt64:
            delete static_cast<const OptionalUInt64Wrapper *>(wrapper);
            break;
        case Type::Int8:
            delete static_cast<const OptionalInt8Wrapper *>(wrapper);
            break;
        case Type::Int16:
            delete static_cast<const OptionalInt16Wrapper *>(wrapper);
            break;
        case Type::Int32:
            delete static_cast<const OptionalInt32Wrapper *>(wrapper);
            break;
        case Type::Int64:
            delete static_cast<const OptionalInt64Wrapper *>(wrapper);
            break;
        case Type::Int128:
            delete static_cast<const OptionalInt128Wrapper *>(wrapper);
            break;
        case Type::UUID:
            delete static_cast<const OptionalUUIDWrapper *>(wrapper);
            break;
        case Type::Float32:
            delete static_cast<const OptionalFloat32Wrapper *>(wrapper);
            break;
        case Type::Float64:
            delete static_cast<const OptionalFloat64Wrapper *>(wrapper);
            break;
        case Type::Decimal:
            delete static_cast<const OptionalInt128Wrapper *>(wrapper);
            break;
        case Type::Date:
            delete static_cast<const OptionalUInt16Wrapper *>(wrapper);
            break;
        case Type::Date32:
            delete static_cast<const OptionalInt32Wrapper *>(wrapper);
            break;
        case Type::DateTime:
            delete static_cast<const OptionalUInt32Wrapper *>(wrapper);
            break;
        case Type::DateTime64:
            delete static_cast<const OptionalInt64Wrapper *>(wrapper);
            break;
        case Type::Enum8:
            delete static_cast<const OptionalInt8Wrapper *>(wrapper);
            break;
        case Type::Enum16:
            delete static_cast<const OptionalInt16Wrapper *>(wrapper);
            break;
        case Type::String:
        case Type::FixedString:
            delete static_cast<const OptionalStringViewWrapper *>(wrapper);
            break;
        case Type::IPv4:
            delete static_cast<const OptionalUInt32Wrapper *>(wrapper);
            break;
        case Type::IPv6:
            delete static_cast<const OptionalIPv6Wrapper *>(wrapper);
            break;
        default:
            break;
    }
}
