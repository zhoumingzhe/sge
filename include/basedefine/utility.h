#ifndef BASEDEFINE_UTILITY_H
#define BASEDEFINE_UTILITY_H
#include "types.h"
#define get_container(address, type, field)\
    (type*)((sge_uint8*)(address)-(sge_uint8*)(&((type*)0)->field))

#endif
