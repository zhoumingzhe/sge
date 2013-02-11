#include <stdlib.h>
#include "basedefine/type_convert.h"

void run_all_test()
{
    sge_safe_convert_int64_to_int16(sge_int16_max + 1);
}
