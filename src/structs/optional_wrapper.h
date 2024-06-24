#pragma once

#include "int128_wrapper.h"
#include "string_view_wrapper.h"
#include "uuid_wrapper.h"

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

typedef OptionalWrapper(uint32_t, OptionalIPv4Wrapper);

typedef OptionalWrapper(const unsigned char *, OptionalIPv6Wrapper);
