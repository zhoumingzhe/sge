#ifndef BASEDEFINE_TYPES_H
#define BASEDEFINE_TYPES_H
#include "platform.h"

//unsigned builtin types
typedef unsigned char sge_uint8;
typedef unsigned short sge_uint16;
typedef unsigned int sge_uint32;
typedef unsigned long long sge_uint64;

//signed builtin types
typedef char sge_int8;
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

#endif
