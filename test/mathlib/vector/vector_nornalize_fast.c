#include "mathlib/vector.h"
#include "basedefine/runtime_assert.h"
void run_all_test()
{
    sge_vec4f v1 = sge_vec4f_init(3.0f, 0.0f, 0.0f, 4.0f);
    sge_vec4f v2 = sge_vec4f_init(0.6f, 0.0f, 0.0f, 0.8f);
    sge_vec4f v3 = sge_vec4f_nmlz_fast(v1);
    sge_vec4f v4 = sge_vec4f_rep(0.001f);
    sge_runtime_assert(sge_vec4f_near_eql(v2, v3, v4));
}