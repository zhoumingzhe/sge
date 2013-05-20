#include "basedefine/types.h"
#include <xmmintrin.h>

typedef __m128 sge_vec4f;
typedef sge_float32 sge_vec4f_unalign[4];

#define sge_vec4f_zero() _mm_setzero_ps()
#define sge_vec4f_rep(val) _mm_set_ps1(val)

sge_inline sge_bool sge_vec4f_eql(sge_vec4f val1, sge_vec4f val2)
{
    sge_vec4f temp = _mm_cmpeq_ps(val1,val2);
    return ((_mm_movemask_ps(temp)==0x0f) != 0);
}

