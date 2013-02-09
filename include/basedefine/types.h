#ifndef BASEDEFINE_TYPES_H
#define BASEDEFINE_TYPES_H
#include "platform.h"

//builtin type definitions
typedef unsigned char sge_uint8;
typedef unsigned short sge_uint16;
typedef unsigned int sge_uint32;
typedef unsigned long long sge_uint64;

//signed builtin types
typedef signed char sge_int8;
typedef short sge_int16;
typedef int sge_int32;
typedef long long sge_int64;

#ifdef SGE_32
typedef unsigned int sge_size_t;
typedef int sge_ssize_t;
#endif

#ifdef SGE_64
typedef unsigned long long sge_size_t;
typedef long long sge_ssize_t;
#endif

typedef float sge_float32;
typedef double sge_float64;

//builtin type limitations
#define sge_uint8_max 0xff
#define sge_int8_max 127
#define sge_int8_min (-128)

#define sge_uint16_max 0xffff
#define sge_int16_max 32767
#define sge_int16_min (-32768)

#define sge_uint32_max 0xffffffff
#define sge_int32_max 2147483647
#define sge_int32_min (-2147483647-1)

#define sge_uint64_max 0xffffffffffffffffULL
#define sge_int64_max 9223372036854775807LL
#define sge_int64_min (-9223372036854775807LL-1)

#endif
