#include <stdlib.h>
#include "basedefine/type_convert.h"

void run_all_test()
{
    sge_safe_convert_uint64_to_uint16(sge_uint16_max + 1);
}
