#ifndef MATHLIB_VECTOR_H
#define MATHLIB_VECTOR_H
#include "basedefine/types.h"
#include <xmmintrin.h>
#include <emmintrin.h>
SGE_EXTERN_C_START
//-----------------------------typedefs--------------------
typedef __m128 sge_vec4f;
typedef __m128i sge_vec4i;
typedef __m128d sge_vec2d;

typedef sge_float32 sge_vec4f_unaligned[4];
typedef sge_int32 sge_vec4i_unaligned[4];
typedef sge_float64 sge_vec2d_unaligned[2];

typedef sge_align(16) sge_float32 sge_vec4f_aligned[4];
typedef sge_align(16) sge_int32 sge_vec4i_aligned[4];
typedef sge_align(16) sge_float64 sge_vec2d_aligned[2];

//--------------------------constants---------------------

extern const sge_vec4f_aligned sge_vec4f_no_fraction;
extern const sge_vec4f_aligned sge_vec4f_1000;
extern const sge_vec4f_aligned sge_vec4f_0100;
extern const sge_vec4f_aligned sge_vec4f_0010;
extern const sge_vec4f_aligned sge_vec4f_0001;
extern const sge_vec4f_aligned sge_vec4f_neg_1000;
extern const sge_vec4f_aligned sge_vec4f_neg_0100;
extern const sge_vec4f_aligned sge_vec4f_neg_0010;
extern const sge_vec4f_aligned sge_vec4f_neg_0001;



extern const sge_vec4i_aligned sge_onehalf_eps;
extern const sge_vec4i_aligned sge_abs_mask;
extern const sge_vec4i_aligned sge_x_mask;
extern const sge_vec4i_aligned sge_y_mask;
extern const sge_vec4i_aligned sge_z_mask;
extern const sge_vec4i_aligned sge_w_mask;
extern const sge_vec4i_aligned sge_xyz_mask;

//sse shuffle macro, internal use only
#define sge_sse_shuffle(f0, f1, f2, f3)\
    (((f3) << 6) | ((f2) << 4) | ((f1) << 2) | ((f0)))

//---------------initialization functions-----------------

#define sge_vec4f_zero() _mm_setzero_ps()
#define sge_vec4f_rep(val) _mm_set_ps1(val)
#define sge_vec4f_init(x, y, z, w) _mm_set_ps(w, z, y, x)
#define sge_vec4i_init(x, y, z, w) _mm_set_epi32(w, z, y, x)
//------------------memory access function----------------

#define sge_vec4f_load_aligned(addr) _mm_load_ps(addr)
#define sge_vec4i_load_aligned(addr) _mm_load_si128((sge_vec4i*)addr)
#define sge_vec4f_store_aligned(addr, val) _mm_store_ps(addr, val)
#define sge_vec4i_store_aligned(addr, val) _mm_store_si128((sge_vec4i*)add, val)

#define sge_vec4f_load_unaligned(addr) _mm_loadu_ps(addr)
#define sge_vec4i_load_unaligned(addr) _mm_loadu_si128((sge_vec4i*)addr)
#define sge_vec4f_store_unaligned(addr, val) _mm_storeu_ps(addr, val)
#define sge_vec4i_store_unaligned(addr, val) _mm_storeu_si128((sge_vec4i*)add, val)

//--------------------access functions-------------------

#define sge_vec4f_getx(val) _mm_cvtss_f32(val)
sge_inline float sge_vec4f_gety(sge_vec4f val)
{
    sge_vec4f val1 = _mm_shuffle_ps(val, val, sge_sse_shuffle(1, 1, 1, 1));
    return _mm_cvtss_f32(val1);
}

sge_inline float sge_vec4f_getz(sge_vec4f val)
{
    sge_vec4f val1 = _mm_shuffle_ps(val, val, sge_sse_shuffle(2, 2, 2, 2));
    return _mm_cvtss_f32(val1);
}

sge_inline float sge_vec4f_getw(sge_vec4f val)
{
    sge_vec4f val1 = _mm_shuffle_ps(val, val, sge_sse_shuffle(3, 3, 3, 3));
    return _mm_cvtss_f32(val1);
}

sge_inline sge_vec4f sge_vec4f_setx(sge_vec4f val, sge_float32 x)
{
    sge_vec4f tmp = _mm_set_ss(x);
    return _mm_move_ss(val,tmp);
}

sge_inline sge_vec4f sge_vec4f_sety(sge_vec4f val, sge_float32 x)
{
    sge_vec4f tmp = _mm_set_ss(x);
    sge_vec4f shf = _mm_shuffle_ps(val, val, sge_sse_shuffle(1, 0, 2, 3));
    shf = _mm_move_ss(shf, tmp);

    return _mm_shuffle_ps(shf, shf, sge_sse_shuffle(1, 0, 2, 3));
}

sge_inline sge_vec4f sge_vec4f_setz(sge_vec4f val, sge_float32 x)
{
    sge_vec4f tmp = _mm_set_ss(x);
    sge_vec4f shf = _mm_shuffle_ps(val, val, sge_sse_shuffle(2, 1, 0, 3));
    shf = _mm_move_ss(shf, tmp);

    return _mm_shuffle_ps(shf, shf, sge_sse_shuffle(2, 1, 0, 3));
}

sge_inline sge_vec4f sge_vec4f_setw(sge_vec4f val, sge_float32 x)
{
    sge_vec4f tmp = _mm_set_ss(x);
    sge_vec4f shf = _mm_shuffle_ps(val, val, sge_sse_shuffle(3, 1, 2, 0));
    shf = _mm_move_ss(shf, tmp);

    return _mm_shuffle_ps(shf, shf, sge_sse_shuffle(3, 1, 2, 0));
}

//---------------------arithmetic functions---------------

#define sge_vec4f_max(val1, val2) _mm_max_ps(val1, val2)
#define sge_vec4f_min(val1, val2) _mm_min_ps(val1, val2)
#define sge_vec4f_add(val1, val2) _mm_add_ps(val1, val2)
#define sge_vec4f_sub(val1, val2) _mm_sub_ps(val1, val2)
#define sge_vec4f_mul(val1, val2) _mm_mul_ps(val1, val2)
#define sge_vec4f_div(val1, val2) _mm_div_ps(val1, val2)
#define sge_vec4f_rcp_fast(val) _mm_rcp_ps(val)
#define sge_vec4f_div_fast(val1, val2) sge_vec4f_mul(val1, sge_vec4f_rcp_fast(val2))

sge_inline sge_vec4f sge_vec4f_scale(sge_vec4f val, sge_float32 scale)
{
    sge_vec4f temp = sge_vec4f_rep(scale);
    return sge_vec4f_mul(val, temp);
}

sge_inline sge_vec4f sge_vec4f_abs(sge_vec4f val)
{
    sge_vec4f temp = sge_vec4f_zero();
    temp = sge_vec4f_sub(temp, val);
    return sge_vec4f_max(temp, val);
}

sge_inline sge_vec4f sge_vec4f_clamp(sge_vec4f val, sge_vec4f minval, sge_vec4f maxval)
{
    sge_vec4f temp = sge_vec4f_max(val, minval);
    return sge_vec4f_min(temp, maxval);
}

sge_inline sge_vec4f sge_vec4f_floor(sge_vec4f val)
{
    sge_vec4f result = _mm_sub_ps(val, _mm_castsi128_ps(sge_vec4i_load_aligned(sge_onehalf_eps)));
    sge_vec4i vInt = _mm_cvtps_epi32(result);
    sge_vec4i abs_int = _mm_and_si128(_mm_castps_si128(val), sge_vec4i_load_aligned(sge_abs_mask));

    abs_int = _mm_cmplt_epi32(abs_int, sge_vec4i_load_aligned(sge_vec4f_no_fraction));
    result = _mm_cvtepi32_ps(vInt);
    result = _mm_and_ps(result, _mm_castsi128_ps(abs_int));
    abs_int = _mm_andnot_si128(abs_int, _mm_castps_si128(val));
    result = _mm_or_ps(result, _mm_castsi128_ps(abs_int));
    return result;
}

sge_inline sge_vec4f sge_vec4f_celling(sge_vec4f val)
{
    sge_vec4f result = _mm_add_ps(val, _mm_castsi128_ps(sge_vec4i_load_aligned(sge_onehalf_eps)));
    sge_vec4i vInt = _mm_cvtps_epi32(result);
    sge_vec4i abs_int = _mm_and_si128(_mm_castps_si128(val), sge_vec4i_load_aligned(sge_abs_mask));

    abs_int = _mm_cmplt_epi32(abs_int, sge_vec4i_load_aligned(sge_vec4f_no_fraction));
    result = _mm_cvtepi32_ps(vInt);
    result = _mm_and_ps(result, _mm_castsi128_ps(abs_int));
    abs_int = _mm_andnot_si128(abs_int, _mm_castps_si128(val));
    result = _mm_or_ps(result, _mm_castsi128_ps(abs_int));
    return result;
}

sge_inline sge_vec4f sge_vec4f_select(sge_vec4f val1, sge_vec4f val2, sge_vec4f control)
{
    sge_vec4f t1 = _mm_andnot_ps(control, val1);
    sge_vec4f t2 = _mm_and_ps(val2, control);
    return _mm_or_ps(t1, t2);
}

sge_inline sge_vec4f sge_vec4f_neg(sge_vec4f val)
{
    sge_vec4f zero = _mm_setzero_ps();
    return _mm_sub_ps(zero, val);
}
//--------------comparison functions-------------------
sge_inline sge_bool sge_vec4f_eql(sge_vec4f val1, sge_vec4f val2)
{
    sge_vec4f temp = _mm_cmpeq_ps(val1,val2);
    return (_mm_movemask_ps(temp)==0x0f);
}

sge_inline sge_bool sge_vec4f_eqlx(sge_vec4f val, float x)
{
    sge_vec4f temp = _mm_set_ss(x);
    return (_mm_ucomieq_ss(val, temp));
}

sge_inline sge_bool sge_vec4f_eqly(sge_vec4f val, float y)
{
    sge_vec4f temp = _mm_set_ss(y);
    sge_vec4f temp1 = _mm_shuffle_ps(val, val, sge_sse_shuffle(1, 1, 1, 1));
    return (_mm_ucomieq_ss(temp, temp1));
}

sge_inline sge_bool sge_vec4f_eqlz(sge_vec4f val, float z)
{
    sge_vec4f temp = _mm_set_ss(z);
    sge_vec4f temp1 = _mm_shuffle_ps(val, val, sge_sse_shuffle(2, 2, 2, 2));
    return (_mm_ucomieq_ss(temp, temp1));
}

sge_inline sge_bool sge_vec4f_eqlw(sge_vec4f val, float w)
{
    sge_vec4f temp = _mm_set_ss(w);
    sge_vec4f temp1 = _mm_shuffle_ps(val, val, sge_sse_shuffle(3, 3, 3, 3));
    return (_mm_ucomieq_ss(temp, temp1));
}

sge_inline sge_bool sge_vec4f_lt(sge_vec4f val1, sge_vec4f val2)
{
    sge_vec4f temp = _mm_cmplt_ps(val1,val2);
    return (_mm_movemask_ps(temp)==0x0f);
}

sge_inline sge_bool sge_vec4f_near_eql(sge_vec4f val1, sge_vec4f val2, sge_vec4f tolerance)
{
    sge_vec4f delta = sge_vec4f_sub(val1, val2);
    delta = sge_vec4f_abs(delta);
    return sge_vec4f_lt(delta, tolerance);
}

//---------------------------geometric functions-------------------------
sge_inline sge_vec4f sge_vec4f_lerp(sge_vec4f val1, sge_vec4f val2, sge_float32 t)
{
    sge_vec4f l = sge_vec4f_sub(val2, val1);
    sge_vec4f s = sge_vec4f_rep(t);
    sge_vec4f result = sge_vec4f_mul(l, s);
    return sge_vec4f_add(result, val1);
}

sge_inline sge_vec4f sge_vec4f_lerp_vec4f(sge_vec4f val1, sge_vec4f val2, sge_vec4f t)
{
    sge_vec4f l = sge_vec4f_sub(val2, val1);
    sge_vec4f result = sge_vec4f_mul(l, t);
    return sge_vec4f_add(result, val1);
}

sge_inline sge_vec4f sge_vec4f_cross3(sge_vec4f val1, sge_vec4f val2)
{
    //(x1*y2-y1*x2,z1*x2-x1*z2, y1*z2-z1*y2,0)
    sge_vec4f t1 = _mm_shuffle_ps(val1, val1, sge_sse_shuffle(1, 2, 0, 3));
    sge_vec4f t2 = _mm_shuffle_ps(val2, val2, sge_sse_shuffle(2, 0, 1, 3));
    sge_vec4f ret = _mm_mul_ps(t1, t2);

    t1 = _mm_shuffle_ps(t1, t1, sge_sse_shuffle(1, 2, 0, 3));
    t2 = _mm_shuffle_ps(t2, t2, sge_sse_shuffle(2, 0, 1, 3));
    t1 = _mm_mul_ps(t1,t2);
    ret = _mm_sub_ps(ret,t1);
    return _mm_andnot_ps(_mm_castsi128_ps(sge_vec4i_load_aligned(sge_w_mask)), ret);
}

sge_inline sge_vec4f sge_vec4f_dot(sge_vec4f val1, sge_vec4f val2)
{
    sge_vec4f t1 = sge_vec4f_mul(val1, val2);
    sge_vec4f t2 = _mm_shuffle_ps(t1, t1, sge_sse_shuffle(1, 0, 3, 2));
    t2 = sge_vec4f_add(t1, t2);
    t1 = _mm_shuffle_ps(t2, t2, sge_sse_shuffle(2, 3, 0, 1));
    return sge_vec4f_add(t1, t2);
}

sge_inline sge_vec4f sge_vec4f_nmlz_fast(sge_vec4f val)
{
    sge_vec4f lengthsq = sge_vec4f_dot(val, val);
    lengthsq = _mm_rsqrt_ps(lengthsq);
    return _mm_mul_ps(lengthsq, val);
}
SGE_EXTERN_C_END
#endif