#pragma once

#include <clickhouse/types/types.h>

#include "structs/int128_wrapper.h"
#include "structs/string_view_wrapper.h"
#include "structs/uuid_wrapper.h"
#include "export.h"
#include "clickhouse/base/socket.h"

using namespace clickhouse;

enum chc_optional_type : uint8_t {
    invalid,
    null,
    uint8,
    uint16,
    uint32,
    uint64,
    int8,
    int16,
    int32,
    int64,
    int128,
    uuid,
    float32,
    float64,
    string_view,
    ipv6,
};

struct chc_optional {
    chc_optional_type type;

    union {
        uint8_t uint8;
        uint16_t uint16;
        uint32_t uint32;
        uint64_t uint64;
        int8_t int8;
        int16_t int16;
        int32_t int32;
        int64_t int64;
        chc_int128 int128;
        chc_uuid uuid;
        float float32;
        double float64;
        chc_string_view string_view;
        in6_addr ipv6;
    } value;
};

// #define chc_optional(type, name) struct { bool has_value; type value; } name;
//
//
// typedef chc_optional(chc_string_view, chc_optional_string_view);
//
// typedef chc_optional(int8_t, chc_optional_int8);
//
// typedef chc_optional(int16_t, chc_optional_int16);
//
// typedef chc_optional(int32_t, chc_optional_int32);
//
// typedef chc_optional(int64_t, chc_optional_int64);
//
// typedef chc_optional(chc_int128, chc_optional_int128);
//
// typedef chc_optional(uint8_t, chc_optional_uint8);
//
// typedef chc_optional(uint16_t, chc_optional_uint16);
//
// typedef chc_optional(uint32_t, chc_optional_uint32);
//
// typedef chc_optional(uint64_t, chc_optional_uint64);
//
// typedef chc_optional(float, chc_optional_float32);
//
// typedef chc_optional(double, chc_optional_float64);
//
// typedef chc_optional(chc_uuid, chc_optional_uuid);
//
// struct chc_optional_ipv6 {
//     bool has_value;
//     in6_addr value;
// };
//
// extern "C" EXPORT inline void chc_optional_free(const void *wrapper, const Type::Code code) {
//     switch (code) {
//         case Type::UInt8:
//             delete static_cast<const chc_optional_uint8 *>(wrapper);
//             break;
//         case Type::UInt16:
//             delete static_cast<const chc_optional_uint16 *>(wrapper);
//             break;
//         case Type::UInt32:
//             delete static_cast<const chc_optional_uint32 *>(wrapper);
//             break;
//         case Type::UInt64:
//             delete static_cast<const chc_optional_uint64 *>(wrapper);
//             break;
//         case Type::Int8:
//             delete static_cast<const chc_optional_int8 *>(wrapper);
//             break;
//         case Type::Int16:
//             delete static_cast<const chc_optional_int16 *>(wrapper);
//             break;
//         case Type::Int32:
//             delete static_cast<const chc_optional_int32 *>(wrapper);
//             break;
//         case Type::Int64:
//             delete static_cast<const chc_optional_int64 *>(wrapper);
//             break;
//         case Type::Int128:
//             delete static_cast<const chc_optional_int128 *>(wrapper);
//             break;
//         case Type::UUID:
//             delete static_cast<const chc_optional_uuid *>(wrapper);
//             break;
//         case Type::Float32:
//             delete static_cast<const chc_optional_float32 *>(wrapper);
//             break;
//         case Type::Float64:
//             delete static_cast<const chc_optional_float64 *>(wrapper);
//             break;
//         case Type::Decimal:
//             delete static_cast<const chc_optional_int128 *>(wrapper);
//             break;
//         case Type::Date:
//             delete static_cast<const chc_optional_uint16 *>(wrapper);
//             break;
//         case Type::Date32:
//             delete static_cast<const chc_optional_int32 *>(wrapper);
//             break;
//         case Type::DateTime:
//             delete static_cast<const chc_optional_uint32 *>(wrapper);
//             break;
//         case Type::DateTime64:
//             delete static_cast<const chc_optional_int64 *>(wrapper);
//             break;
//         case Type::Enum8:
//             delete static_cast<const chc_optional_int8 *>(wrapper);
//             break;
//         case Type::Enum16:
//             delete static_cast<const chc_optional_int16 *>(wrapper);
//             break;
//         case Type::String:
//         case Type::FixedString:
//             delete static_cast<const chc_optional_string_view *>(wrapper);
//             break;
//         case Type::IPv4:
//             delete static_cast<const chc_optional_uint32 *>(wrapper);
//             break;
//         case Type::IPv6:
//             delete static_cast<const chc_optional_ipv6 *>(wrapper);
//             break;
//         default:
//             break;
//     }
// }
