#ifndef MATHLIB_MATRIX_H
#define MATHLIB_MATRIX_H
#include "vector.h"
typedef sge_align(16) union sge_mat44f
{
    sge_vec4f r[4];
    struct
    {
        float _11, _12, _13, _14;
        float _21, _22, _23, _24;
        float _31, _32, _33, _34;
        float _41, _42, _43, _44;
    };
    sge_float32 m[4][4];
}sge_mat44f;

sge_mat44f sge_mat44f_identity()
{
    sge_mat44f ret;
    ret.r[0] = sge_vec4f_load_aligned(sge_vec4f_1000);
    ret.r[1] = sge_vec4f_load_aligned(sge_vec4f_0100);
    ret.r[2] = sge_vec4f_load_aligned(sge_vec4f_0010);
    ret.r[3] = sge_vec4f_load_aligned(sge_vec4f_0001);
    return ret;
}

sge_mat44f sge_mat44f_translate(sge_float32 x, sge_float32 y, sge_float32 z)
{
    sge_mat44f ret;
    ret.r[0] = sge_vec4f_load_aligned(sge_vec4f_1000);
    ret.r[1] = sge_vec4f_load_aligned(sge_vec4f_0100);
    ret.r[2] = sge_vec4f_load_aligned(sge_vec4f_0010);
    ret.r[3] = sge_vec4f_init(x, y, z, 1.f);
    return ret;
}

#endif