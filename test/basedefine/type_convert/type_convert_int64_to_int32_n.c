#include <stdlib.h>
#include "basedefine/type_convert.h"

void run_all_test()
{
    sge_safe_convert_int64_to_int32((sge_int64)sge_int32_min - 1);
}
