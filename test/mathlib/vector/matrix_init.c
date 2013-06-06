#include "mathlib/matrix.h"
#include "basedefine/runtime_assert.h"
void run_all_test()
{
    sge_mat44f mat = sge_mat44f_identity();
    sge_runtime_assert(sge_vec4f_eql(mat.r[0], sge_vec4f_init(1.f, 0.f, 0.f, 0.f)));
    sge_runtime_assert(sge_vec4f_eql(mat.r[1], sge_vec4f_init(0.f, 1.f, 0.f, 0.f)));
    sge_runtime_assert(sge_vec4f_eql(mat.r[2], sge_vec4f_init(0.f, 0.f, 1.f, 0.f)));
    sge_runtime_assert(sge_vec4f_eql(mat.r[3], sge_vec4f_init(0.f, 0.f, 0.f, 1.f)));
}