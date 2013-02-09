#include "basedefine/type_convert.h"

void run_all_test()
{
    sge_uint8 u = sge_safe_convert_sge_uint16_to_sge_uint8((sge_uint16)65530);
    UNUSED(u);
}
