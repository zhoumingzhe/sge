#include "basedefine/types.h"
#include <xmmintrin.h>

typedef __m128 sge_vec4f;
typedef sge_float32 sge_vec4f_unalign[4];

//sse shuffle macro, internal use only
#define sge_sse_shuffle(f3, f2, f1, f0)\
    (((f3) << 6) | ((f2) << 4) | ((f1) << 2) | ((f0)))

//initialization functions
#define sge_vec4f_zero() _mm_setzero_ps()
#define sge_vec4f_rep(val) _mm_set_ps1(val)
#define sge_vec4f_init(x, y, z, w) _mm_set_ps(w, z, y, x)

//access functions
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

//comparison functions
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