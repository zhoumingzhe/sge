#ifndef MATHLIB_MATRIX_H
#define MATHLIB_MATRIX_H
#include "vector.h"
SGE_EXTERN_C_START
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

sge_inline sge_mat44f sge_mat44f_identity()
{
    sge_mat44f ret;
    ret.r[0] = sge_vec4f_load_aligned(sge_vec4f_1000);
    ret.r[1] = sge_vec4f_load_aligned(sge_vec4f_0100);
    ret.r[2] = sge_vec4f_load_aligned(sge_vec4f_0010);
    ret.r[3] = sge_vec4f_load_aligned(sge_vec4f_0001);
    return ret;
}

sge_inline sge_mat44f sge_mat44f_translate(sge_float32 x, sge_float32 y, sge_float32 z)
{
    sge_mat44f ret;
    ret.r[0] = sge_vec4f_load_aligned(sge_vec4f_1000);
    ret.r[1] = sge_vec4f_load_aligned(sge_vec4f_0100);
    ret.r[2] = sge_vec4f_load_aligned(sge_vec4f_0010);
    ret.r[3] = sge_vec4f_init(x, y, z, 1.f);
    return ret;
}

/**************************************************************************
Right-hand DirectX projection matrix
2n/w,   0,      0,          0
0,      2n/h,   0,          0
0,      0,      f/(n-f),    -1
0,      0,      nf/(n-f),   0

(0,0,-n,1)*m=(0,0,0,n)--->(0,0,0)
(0,0,-f,1)*m=(0,0,f,f)--->(0,0,1)
**************************************************************************/
sge_inline sge_mat44f sge_mat44f_perspective_rh_dx(sge_float32 width, sge_float32 height, sge_float32 n, sge_float32 f)
{
    sge_mat44f M;
    sge_vec4f t1 = sge_vec4f_init(n, n, f, f);
    sge_vec4f t2 = sge_vec4f_init(2.0f, 2.0f, 1.0f, n);
    sge_vec4f t3 = sge_vec4f_init(width, height, f, f);
    sge_vec4f t4 = sge_vec4f_init(0, 0, n, n);

    t3 = sge_vec4f_sub(t3, t4);

    t1 = sge_vec4f_mul(t1, t2);
    t1 = sge_vec4f_div(t1, t3); //t1={2n/width,2n/height,f/(f-n),nf/(f-n)}

    t2 = sge_vec4f_zero(); 
    M.r[0] = _mm_move_ss(t2, t1);
    M.r[1] = _mm_and_ps(t1, _mm_castsi128_ps(sge_vec4i_load_unaligned(sge_y_mask)));

    //t3 = {f/(f-n),nf/(f-n),0,-1}
    t3 = _mm_shuffle_ps(t1, sge_vec4f_load_aligned(sge_vec4f_neg_0001), sge_sse_shuffle(2,3,2,3));

    M.r[2] = _mm_shuffle_ps(t2, t3, sge_sse_shuffle(0,0,0,3));
    M.r[3] = _mm_shuffle_ps(t2, t3, sge_sse_shuffle(0,0,1,2));
    return M;
}

/**************************************************************************
Right-hand OpenGL projection matrix
2n/w,   0,      0,              0
0,      2n/h,   0,              0
0,      0,      (f+n)/(n-f),    -1
0,      0,      2fn/(n-f),      0

(0,0,-n,1)*m=(0,0,-n,n)--->(0,0,0)
(0,0,-f,1)*m=(0,0,f,f)--->(0,0,1)
(
**************************************************************************/
sge_inline sge_mat44f sge_mat44f_perspective_rh_gl(sge_float32 width, sge_float32 height, sge_float32 n, sge_float32 f)
{
    sge_mat44f M;
    sge_vec4f t1 = sge_vec4f_init(n, n, f, f);
    sge_vec4f t2 = sge_vec4f_init(n, n, n, f);
    sge_vec4f t3 = sge_vec4f_init(1.0f, 1.0f, 1.0f, n);

    sge_vec4f t4 = sge_vec4f_init(width, height, f, f);
    sge_vec4f t5 = sge_vec4f_init(0, 0, n, n);

    t4 = sge_vec4f_sub(t4, t5);

    t1 = sge_vec4f_add(t1, t2);
    t1 = sge_vec4f_mul(t1, t3);

    t1 = sge_vec4f_div(t1, t4); //t1={2n/width,2n/height,(f+n)/(f-n),2nf/(f-n)}

    t2 = sge_vec4f_zero(); 
    M.r[0] = _mm_move_ss(t2, t1);
    M.r[1] = _mm_and_ps(t1, _mm_castsi128_ps(sge_vec4i_load_unaligned(sge_y_mask)));

    //t3 = {(f+n)/(f-n),2nf/(f-n),0,-1}
    t3 = _mm_shuffle_ps(t1, sge_vec4f_load_aligned(sge_vec4f_neg_0001), sge_sse_shuffle(2,3,2,3));

    M.r[2] = _mm_shuffle_ps(t2, t3, sge_sse_shuffle(0,0,0,3));
    M.r[3] = _mm_shuffle_ps(t2, t3, sge_sse_shuffle(0,0,1,2));
    return M;
}
SGE_EXTERN_C_END
#endif