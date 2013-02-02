#include "basedefine/static_assert.h"
#include "basedefine/types.h"
//static assert is enough
sge_static_assert(sizeof(sge_uint8) == 1);
sge_static_assert(sizeof(sge_uint16) == 2);
sge_static_assert(sizeof(sge_uint32) == 4);
sge_static_assert(sizeof(sge_uint64) == 8);

sge_static_assert(sizeof(sge_int8) == 1);
sge_static_assert(sizeof(sge_int16) == 2);
sge_static_assert(sizeof(sge_int32) == 4);
sge_static_assert(sizeof(sge_int64) == 8);

sge_static_assert(sizeof(sge_size_t) == sizeof(void*));
sge_static_assert(sizeof(sge_ssize_t) == sizeof(void*));

sge_static_assert(sizeof(sge_float32) == 4);
sge_static_assert(sizeof(sge_float64) == 8);

sge_static_assert((sge_uint8)(-1) > 0);
sge_static_assert((sge_uint16)(-1) > 0);
sge_static_assert((sge_uint32)(-1) > 0);
sge_static_assert((sge_uint64)(-1) > 0);


sge_static_assert((sge_int8)(-1) < 0);
sge_static_assert((sge_int16)(-1) < 0);
sge_static_assert((sge_int32)(-1) < 0);
sge_static_assert((sge_int64)(-1) < 0);

void run_all_test()
{
}