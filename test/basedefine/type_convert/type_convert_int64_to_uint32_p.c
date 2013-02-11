#include <stdlib.h>
#include "basedefine/type_convert.h"

void run_all_test()
{
    sge_safe_convert_int64_to_uint32((sge_int64)sge_uint32_max + 1);
}
