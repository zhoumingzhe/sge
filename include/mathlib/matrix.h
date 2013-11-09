#ifndef MATHLIB_MATRIX_H
#define MATHLIB_MATRIX_H
#include <math.h>
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
#define sge_mat44f_transpose(m) _sge_mat44f_transpose(&m)
sge_inline sge_mat44f _sge_mat44f_transpose(const sge_mat44f* m)
{
    sge_vec4f t1 = _mm_shuffle_ps(m->r[0], m->r[1], sge_sse_shuffle(0,1,0,1));
    // x.z,x.w,y.z,y.w
    sge_vec4f t3 = _mm_shuffle_ps(m->r[0],m->r[1],sge_sse_shuffle(2,3,2,3));
    // z.x,z.y,w.x,w.y
    sge_vec4f t2 = _mm_shuffle_ps(m->r[2],m->r[3],sge_sse_shuffle(0,1,0,1));
    // z.z,z.w,w.z,w.w
    sge_vec4f t4 = _mm_shuffle_ps(m->r[2],m->r[3],sge_sse_shuffle(2,3,2,3));
    sge_mat44f result;

    // x.x,y.x,z.x,w.x
    result.r[0] = _mm_shuffle_ps(t1, t2,sge_sse_shuffle(0,2,0,2));
    // x.y,y.y,z.y,w.y
    result.r[1] = _mm_shuffle_ps(t1, t2,sge_sse_shuffle(1,3,1,3));
    // x.z,y.z,z.z,w.z
    result.r[2] = _mm_shuffle_ps(t3, t4,sge_sse_shuffle(0,2,0,2));
    // x.w,y.w,z.w,w.w
    result.r[3] = _mm_shuffle_ps(t3, t4,sge_sse_shuffle(1,3,1,3));
    return result;
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

    sge_vec4f t4 = sge_vec4f_init(width, height, n, n);
    sge_vec4f t5 = sge_vec4f_init(0, 0, f, f);

    t4 = sge_vec4f_sub(t4, t5);

    t1 = sge_vec4f_add(t1, t2);
    t1 = sge_vec4f_mul(t1, t3);

    t1 = sge_vec4f_div(t1, t4); //t1={2n/width,2n/height,(f+n)/(n-f),2nf/(n-f)}

    t2 = sge_vec4f_zero(); 
    M.r[0] = _mm_move_ss(t2, t1);
    M.r[1] = _mm_and_ps(t1, _mm_castsi128_ps(sge_vec4i_load_unaligned(sge_y_mask)));

    //t3 = {(f+n)/(f-n),2nf/(f-n),0,-1}
    t3 = _mm_shuffle_ps(t1, sge_vec4f_load_aligned(sge_vec4f_neg_0001), sge_sse_shuffle(2,3,2,3));

    M.r[2] = _mm_shuffle_ps(t2, t3, sge_sse_shuffle(0,0,0,3));
    M.r[3] = _mm_shuffle_ps(t2, t3, sge_sse_shuffle(0,0,1,2));
    return M;
}

sge_inline sge_mat44f sge_mat44f_lookat_rh(sge_vec4f eye, sge_vec4f center, sge_vec4f up)
{
    sge_vec4f negeyedir = sge_vec4f_sub(eye, center);

    sge_vec4f R2 = sge_vec4f_nmlz_fast(negeyedir);

    sge_vec4f R0 = sge_vec4f_nmlz_fast(sge_vec4f_cross3(up, R2));

    sge_vec4f R1 = sge_vec4f_cross3(R2, R0);

    sge_vec4f eyedir = sge_vec4f_neg(negeyedir);

    sge_vec4f D0 = sge_vec4f_dot(R0, eyedir);
    sge_vec4f D1 = sge_vec4f_dot(R1, eyedir);
    sge_vec4f D2 = sge_vec4f_dot(R2, eyedir);

    sge_mat44f M;
    sge_vec4f selector = _mm_castsi128_ps(sge_vec4i_init(-1,-1,-1,0));
    M.r[0] = sge_vec4f_select(D0, R0, selector);
    M.r[1] = sge_vec4f_select(D1, R1, selector);
    M.r[2] = sge_vec4f_select(D2, R2, selector);
    M.r[3] = sge_vec4f_load_aligned(sge_vec4f_0001);

    return sge_mat44f_transpose(M);
}
#define sge_mat44f_mul(mat1, mat2) _sge_mat44f_mul(&mat1, &mat2)
sge_inline sge_mat44f _sge_mat44f_mul(sge_mat44f *mat1, sge_mat44f *mat2)
{
    sge_mat44f mResult;
    sge_vec4f vW = mat1->r[0];
    sge_vec4f vX = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(0,0,0,0));
    sge_vec4f vY = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(1,1,1,1));
    sge_vec4f vZ = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(2,2,2,2));
    vW = _mm_shuffle_ps(vW,vW,_MM_SHUFFLE(3,3,3,3));
    vX = _mm_mul_ps(vX,mat2->r[0]);
    vY = _mm_mul_ps(vY,mat2->r[1]);
    vZ = _mm_mul_ps(vZ,mat2->r[2]);
    vW = _mm_mul_ps(vW,mat2->r[3]);
    vX = _mm_add_ps(vX,vZ);
    vY = _mm_add_ps(vY,vW);
    vX = _mm_add_ps(vX,vY);
    mResult.r[0] = vX;
    vW = mat1->r[1];
    vX = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(0,0,0,0));
    vY = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(1,1,1,1));
    vZ = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(2,2,2,2));
    vW = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(3,3,3,3));
    vX = _mm_mul_ps(vX,mat2->r[0]);
    vY = _mm_mul_ps(vY,mat2->r[1]);
    vZ = _mm_mul_ps(vZ,mat2->r[2]);
    vW = _mm_mul_ps(vW,mat2->r[3]);
    vX = _mm_add_ps(vX,vZ);
    vY = _mm_add_ps(vY,vW);
    vX = _mm_add_ps(vX,vY);
    mResult.r[1] = vX;
    vW = mat1->r[2];
    vX = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(0,0,0,0));
    vY = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(1,1,1,1));
    vZ = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(2,2,2,2));
    vW = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(3,3,3,3));
    vX = _mm_mul_ps(vX,mat2->r[0]);
    vY = _mm_mul_ps(vY,mat2->r[1]);
    vZ = _mm_mul_ps(vZ,mat2->r[2]);
    vW = _mm_mul_ps(vW,mat2->r[3]);
    vX = _mm_add_ps(vX,vZ);
    vY = _mm_add_ps(vY,vW);
    vX = _mm_add_ps(vX,vY);
    mResult.r[2] = vX;
    vW = mat1->r[3];
    vX = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(0,0,0,0));
    vY = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(1,1,1,1));
    vZ = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(2,2,2,2));
    vW = _mm_shuffle_ps(vW,vW,sge_sse_shuffle(3,3,3,3));
    vX = _mm_mul_ps(vX,mat2->r[0]);
    vY = _mm_mul_ps(vY,mat2->r[1]);
    vZ = _mm_mul_ps(vZ,mat2->r[2]);
    vW = _mm_mul_ps(vW,mat2->r[3]);
    vX = _mm_add_ps(vX,vZ);
    vY = _mm_add_ps(vY,vW);
    vX = _mm_add_ps(vX,vY);
    mResult.r[3] = vX;
    return mResult;
}

sge_inline sge_mat44f sge_mat44f_scale(float x, float y, float z)
{
    sge_mat44f m;
    m.r[0] = sge_vec4f_init(x, 0, 0, 0);
    m.r[1] = sge_vec4f_init(0, y, 0, 0);
    m.r[2] = sge_vec4f_init(0, 0, z, 0);
    m.r[3] = sge_vec4f_init(0, 0, 0, 1);
    return m;
}

sge_inline sge_mat44f sge_mat44f_rotate(sge_vec4f axis, float angle)
{
    sge_vec4f V0, V1, V2;
    sge_vec4f R0, R1, R2;

    sge_mat44f M;

    sge_vec4f n = sge_vec4f_nmlz_fast(axis);
    float    fSinAngle = sinf(angle);
    float    fCosAngle = cosf(angle);

    sge_vec4f N0 = _mm_shuffle_ps(n, n,sge_sse_shuffle(1,2,0,3));
    sge_vec4f N1 = _mm_shuffle_ps(n, n,sge_sse_shuffle(2,0,1,3));

    sge_vec4f C0 = _mm_set_ps1(fSinAngle);
    sge_vec4f C1 = _mm_set_ps1(fCosAngle);
    sge_vec4f C2 = _mm_set_ps1(1.0f);
    C2 = sge_vec4f_sub(C2, C1);


    V0 = _mm_mul_ps(C2, N0);
    V0 = _mm_mul_ps(V0, N1);

    R0 = _mm_mul_ps(C2, n);
    R0 = _mm_mul_ps(R0, n);
    R0 = _mm_add_ps(R0, C1);

    R1 = _mm_mul_ps(C0, n);
    R1 = _mm_add_ps(R1, V0);
    R2 = _mm_mul_ps(C0, n);
    R2 = _mm_sub_ps(V0,R2);

    V0 = _mm_and_ps(R0,_mm_castsi128_ps(sge_vec4i_load_aligned(sge_xyz_mask)));
    V1 = _mm_shuffle_ps(R1,R2,sge_sse_shuffle(0,2,1,2));
    V1 = _mm_shuffle_ps(V1,V1,sge_sse_shuffle(1,2,3,0));
    V2 = _mm_shuffle_ps(R1,R2,sge_sse_shuffle(1,1,0,0));
    V2 = _mm_shuffle_ps(V2,V2, sge_sse_shuffle(0,2,0,2));

    R2 = _mm_shuffle_ps(V0,V1,sge_sse_shuffle(0,3,0,1));
    R2 = _mm_shuffle_ps(R2,R2,sge_sse_shuffle(0,2,3,1));

    M.r[0] = R2;

    R2 = _mm_shuffle_ps(V0,V1,sge_sse_shuffle(1,3,2,3));
    R2 = _mm_shuffle_ps(R2,R2,sge_sse_shuffle(2,0,3,1));
    M.r[1] = R2;

    V2 = _mm_shuffle_ps(V2,V0,sge_sse_shuffle(0,1,2,3));
    M.r[2] = V2;
    M.r[3] = sge_vec4f_load_aligned(sge_vec4f_0001);
    return M;
}
SGE_EXTERN_C_END
#endif