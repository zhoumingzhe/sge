#include "mathlib/vector.h"
#include "basedefine/runtime_assert.h"
void run_all_test()
{
    sge_vec4f v1 = sge_vec4f_init(0.5f, 1.5f, 2.5f, 3.5f);
    sge_vec4f v2 = sge_vec4f_init(0.0f, 1.0f, 2.0f, 3.0f);
    sge_vec4f v3 = sge_vec4f_init(17.0f, 17.0f, 17.0f, 17.0f);
    sge_vec4f v4 = sge_vec4f_dot(v1, v2);
    sge_runtime_assert(sge_vec4f_eql(v4, v3));
}