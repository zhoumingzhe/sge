#include <stdlib.h>
#include "basedefine/type_convert.h"

void run_all_test()
{
    sge_safe_convert_uint64_to_uint32((sge_uint64)sge_uint32_max + 1);
}
