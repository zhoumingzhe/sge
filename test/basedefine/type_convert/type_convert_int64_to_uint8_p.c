#include <stdlib.h>
#include "basedefine/type_convert.h"

void run_all_test()
{
    sge_safe_convert_int64_to_uint8(sge_uint8_max + 1);
}
