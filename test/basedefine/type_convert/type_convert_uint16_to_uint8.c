#include <stdlib.h>
#include "basedefine/type_convert.h"

void run_all_test()
{
    sge_safe_convert_uint16_to_uint8(sge_uint8_max + 1);
}
