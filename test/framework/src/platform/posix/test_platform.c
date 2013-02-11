#include <stdlib.h>
#include "basedefine/runtime_assert.h"
#include "test_platform.h"
//nothing to setup on posix
void test_platform_exit()
{
    exit(1);
}
void setup_test_enviroment()
{
   sge_set_runtime_assert_exit(test_platform_exit);
}

