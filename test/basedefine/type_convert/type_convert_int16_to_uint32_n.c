#include <stdlib.h>
#include "basedefine/type_convert.h"

void run_all_test()
{
    sge_safe_convert_int16_to_int8(sge_int8_max);
    sge_safe_convert_int32_to_int8(sge_int8_max);
    sge_safe_convert_int64_to_int8(sge_int8_max);

    sge_safe_convert_int16_to_int8(sge_int8_min);
    sge_safe_convert_int32_to_int8(sge_int8_min);
    sge_safe_convert_int64_to_int8(sge_int8_min);

    sge_safe_convert_uint8_to_int8(sge_int8_max);
    sge_safe_convert_uint16_to_int8(sge_int8_max);
    sge_safe_convert_uint32_to_int8(sge_int8_max);
    sge_safe_convert_uint64_to_int8(sge_int8_max);


    sge_safe_convert_int32_to_int16(sge_int16_max);
    sge_safe_convert_int64_to_int16(sge_int16_max);

    sge_safe_convert_int32_to_int16(sge_int16_min);
    sge_safe_convert_int64_to_int16(sge_int16_min);

    sge_safe_convert_uint16_to_int16(sge_int16_max);
    sge_safe_convert_uint32_to_int16(sge_int16_max);
    sge_safe_convert_uint64_to_int16(sge_int16_max);


    sge_safe_convert_int64_to_int32(sge_int32_max);

    sge_safe_convert_int64_to_int32(sge_int32_min);

    sge_safe_convert_uint32_to_int32(sge_int32_max);
    sge_safe_convert_uint64_to_int32(sge_int32_max);


    sge_safe_convert_uint64_to_int64(sge_int64_max);


    sge_safe_convert_uint16_to_uint8(sge_uint8_max);
    sge_safe_convert_uint32_to_uint8(sge_uint8_max);
    sge_safe_convert_uint64_to_uint8(sge_uint8_max);

    sge_safe_convert_int8_to_uint8(sge_int8_max);
    sge_safe_convert_int16_to_uint8(sge_uint8_max);
    sge_safe_convert_int32_to_uint8(sge_uint8_max);
    sge_safe_convert_int64_to_uint8(sge_uint8_max);


    sge_safe_convert_uint32_to_uint16(sge_uint16_max);
    sge_safe_convert_uint64_to_uint16(sge_uint16_max);

    sge_safe_convert_int8_to_uint16(sge_int8_max);
    sge_safe_convert_int16_to_uint16(sge_int16_max);
    sge_safe_convert_int32_to_uint16(sge_uint16_max);
    sge_safe_convert_int64_to_uint16(sge_uint16_max);


    sge_safe_convert_uint64_to_uint32(sge_uint32_max);

    sge_safe_convert_int8_to_uint32(sge_int8_max);
    sge_safe_convert_int16_to_uint32(sge_int16_max);
    sge_safe_convert_int32_to_uint32(sge_int32_max);
    sge_safe_convert_int64_to_uint32(sge_uint32_max);


    sge_safe_convert_int8_to_uint64(sge_int8_max);
    sge_safe_convert_int16_to_uint64(sge_int16_max);
    sge_safe_convert_int32_to_uint64(sge_int32_max);
    sge_safe_convert_int64_to_uint64(sge_int64_max);
}
