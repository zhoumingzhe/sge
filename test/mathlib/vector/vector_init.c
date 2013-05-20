#include "mathlib/vector.h"
#include "basedefine/runtime_assert.h"

void run_all_test()
{
    sge_vec4f v1 = sge_vec4f_zero();
    sge_vec4f v2 = sge_vec4f_rep(0.0f);
    sge_runtime_assert(sge_vec4f_eql(v1, v2));
}