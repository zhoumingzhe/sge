#include <stdlib.h>
#include "basedefine/type_convert.h"

void run_all_test()
{
    sge_uint8 u = sge_safe_convert_uint16_to_uint8((sge_uint16)65530);
    UNUSED(u);
}
