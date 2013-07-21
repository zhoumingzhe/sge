#ifndef BASEDEFINE_UTILITY_H
#define BASEDEFINE_UTILITY_H
#include "types.h"
#define get_container(address, type, field)\
    (type*)((sge_uint8*)(address)-(sge_uint8*)(&((type*)0)->field))

#define align_down(len, alignment)\
    ((len) & ~(alignment - 1))
#define align_up(len, alignment)\
    ((len + alignment - 1)&~(alignment - 1))

#endif
