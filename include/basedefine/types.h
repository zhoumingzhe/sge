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

typedef sge_int8 sge_bool;

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
static const sge_uint8 sge_uint8_max = 0xff;
static const sge_int8 sge_int8_max = 127;
static const sge_int8 sge_int8_min = (-128);

static const sge_uint16 sge_uint16_max = 0xffff;
static const sge_int16 sge_int16_max = 32767;
static const sge_int16 sge_int16_min = (-32768);

static const sge_uint32 sge_uint32_max = 0xffffffffu;
static const sge_int32 sge_int32_max = 2147483647;
static const sge_int32 sge_int32_min = -2147483647-1;

static const sge_uint64 sge_uint64_max = 0xffffffffffffffffULL;
static const sge_int64 sge_int64_max = 9223372036854775807LL;
static const sge_int64 sge_int64_min = -9223372036854775807LL-1;

#endif
