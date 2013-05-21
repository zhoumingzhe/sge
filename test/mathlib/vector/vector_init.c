#include "mathlib/vector.h"
#include "basedefine/runtime_assert.h"
void run_all_test()
{
    sge_vec4f v1 = sge_vec4f_zero();
    sge_vec4f v2 = sge_vec4f_rep(0.0f);
    sge_vec4f v3;
    sge_vec4f v4;

    sge_runtime_assert(sge_vec4f_eql(v1, v2));

    v3 = sge_vec4f_init(0.0f, 0.0f, 0.0f, 0.0f);
    sge_runtime_assert(sge_vec4f_eql(v1, v3));

    v4 = sge_vec4f_init(1.0f, 2.0f, 3.0f, 4.0f);
    sge_runtime_assert(sge_vec4f_getx(v4)==1.0f);
    sge_runtime_assert(sge_vec4f_gety(v4)==2.0f);
    sge_runtime_assert(sge_vec4f_eqlz(v4,3.0f));
    sge_runtime_assert(sge_vec4f_eqlw(v4,4.0f));

}