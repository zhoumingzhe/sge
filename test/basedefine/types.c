#include "basedefine/static_assert.h"
#include "basedefine/types.h"
#include "basedefine/runtime_assert.h"
//static assert is enough
sge_static_assert(sizeof(sge_uint8) == 1, uint8_is_1_byte);
sge_static_assert(sizeof(sge_uint16) == 2, uint16_is_2_byte);
sge_static_assert(sizeof(sge_uint32) == 4, uint32_is_4_byte);
sge_static_assert(sizeof(sge_uint64) == 8, uint64_is_8_byte);

sge_static_assert(sizeof(sge_int8) == 1, int8_is_1_byte);
sge_static_assert(sizeof(sge_int16) == 2, int16_is_2_byte);
sge_static_assert(sizeof(sge_int32) == 4, int32_is_4_byte);
sge_static_assert(sizeof(sge_int64) == 8, int64_is_8_byte);

sge_static_assert(sizeof(sge_size_t) == sizeof(void*), size_t_is_pointer_size);
sge_static_assert(sizeof(sge_ssize_t) == sizeof(void*), ssize_t_is_pointer_size);

sge_static_assert(sizeof(sge_float32) == 4, float32_is_4_byte);
sge_static_assert(sizeof(sge_float64) == 8, float64_is_8_byte);

sge_static_assert((sge_uint8)(-1) > 0, uint8_must_not_less_than_0);
sge_static_assert((sge_uint16)(-1) > 0, uint16_must_not_less_than_0);
sge_static_assert((sge_uint32)(-1) > 0, uint32_must_not_less_than_0);
sge_static_assert((sge_uint64)(-1) > 0, uint64_must_not_less_than_0);
sge_static_assert((sge_size_t)(-1) > 0, size_t_must_not_less_than_0);

sge_static_assert((sge_int8)(-1) < 0, int8_can_be_less_than_0);
sge_static_assert((sge_int16)(-1) < 0, int16_can_be_less_than_0);
sge_static_assert((sge_int32)(-1) < 0, int32_can_be_less_than_0);
sge_static_assert((sge_int64)(-1) < 0, int64_can_be_less_than_0);
sge_static_assert((sge_ssize_t)(-1) < 0, ssize_t_can_be_less_than_0);

void run_all_test()
{
    sge_runtime_assert((sge_uint8)(sge_uint8_max + 1) == 0);
    sge_runtime_assert((sge_uint16)(sge_uint16_max + 1) == 0);
    sge_runtime_assert((sge_uint32)(sge_uint32_max + 1) == 0);
    sge_runtime_assert((sge_uint64)(sge_uint64_max + 1) == 0);

    //avoid gcc warning about integer overflow, we need to convert the max value to unsigned first
    sge_runtime_assert((sge_int8)((sge_uint8)sge_int8_max + 1) == sge_int8_min);
    sge_runtime_assert((sge_int16)((sge_uint16)sge_int16_max + 1) == sge_int16_min);
    sge_runtime_assert((sge_int32)((sge_uint32)sge_int32_max + 1) == sge_int32_min);
    sge_runtime_assert((sge_int64)((sge_uint64)sge_int64_max + 1) == sge_int64_min);

}
