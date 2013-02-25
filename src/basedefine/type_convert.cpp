#include "type_convert.h"
#include "runtime_assert.h"
template<typename t>
sge_inline t sge_get_max();

template<typename t>
sge_inline t sge_get_min();

#define DEF_GET_MAX(type) template<> sge_template_inst_inline type sge_get_max<type>(){ return (type##_max);}
#define DEF_GET_MIN(type) template<> sge_template_inst_inline type sge_get_min<type>(){ return (type##_min);}
#define DEF_GET_MIN_0(type) template<> sge_template_inst_inline type sge_get_min<type>() {return 0;}

DEF_GET_MAX(sge_int8)
DEF_GET_MAX(sge_int16)
DEF_GET_MAX(sge_int32)
DEF_GET_MAX(sge_int64)

DEF_GET_MAX(sge_uint8)
DEF_GET_MAX(sge_uint16)
DEF_GET_MAX(sge_uint32)
DEF_GET_MAX(sge_uint64)

DEF_GET_MIN(sge_int8)
DEF_GET_MIN(sge_int16)
DEF_GET_MIN(sge_int32)
//DEF_GET_MIN(sge_int64)

DEF_GET_MIN_0(sge_uint8)
DEF_GET_MIN_0(sge_uint16)
DEF_GET_MIN_0(sge_uint32)
DEF_GET_MIN_0(sge_uint64)

template<typename to, typename from>
sge_inline to sge_safe_converti(from f)
{
    to to_min = sge_get_min<to>();
    to to_max = sge_get_max<to>();
    if(f<0)
        sge_runtime_assert(to_min<0 && (sge_int64)f >= (sge_int64)to_min);
    else
        sge_runtime_assert((sge_uint64)f <= (sge_uint64)to_max);
    return (to)f;
}

template<typename to, typename from>
sge_inline to sge_safe_convertu(from f)
{
    to to_max = sge_get_max<to>();
    sge_runtime_assert((sge_uint64)f <= (sge_uint64)to_max);
    return (to)f;
}

#define DEF_SAFE_CONVERTI(to, from)\
    template sge_##to sge_safe_converti<sge_##to, sge_##from>(sge_##from f);\
    sge_##to sge_safe_convert_##from##_to_##to(sge_##from f)\
{\
    return sge_safe_converti<sge_##to>(f);\
}

#define DEF_SAFE_CONVERTU(to, from)\
    template sge_##to sge_safe_convertu<sge_##to, sge_##from>(sge_##from f);\
    sge_##to sge_safe_convert_##from##_to_##to(sge_##from f)\
{\
    return sge_safe_convertu<sge_##to>(f);\
}

DEF_SAFE_CONVERTI(int8, int16)
DEF_SAFE_CONVERTI(int8, int32)
DEF_SAFE_CONVERTI(int8, int64)
DEF_SAFE_CONVERTU(int8, uint8)
DEF_SAFE_CONVERTU(int8, uint16)
DEF_SAFE_CONVERTU(int8, uint32)
DEF_SAFE_CONVERTU(int8, uint64)

DEF_SAFE_CONVERTI(int16, int32)
DEF_SAFE_CONVERTI(int16, int64)
DEF_SAFE_CONVERTU(int16, uint16)
DEF_SAFE_CONVERTU(int16, uint32)
DEF_SAFE_CONVERTU(int16, uint64)

DEF_SAFE_CONVERTI(int32, int64)
DEF_SAFE_CONVERTU(int32, uint32)
DEF_SAFE_CONVERTU(int32, uint64)

DEF_SAFE_CONVERTU(int64, uint64)

DEF_SAFE_CONVERTU(uint8, uint16)
DEF_SAFE_CONVERTU(uint8, uint32)
DEF_SAFE_CONVERTU(uint8, uint64)
DEF_SAFE_CONVERTI(uint8, int8)
DEF_SAFE_CONVERTI(uint8, int16)
DEF_SAFE_CONVERTI(uint8, int32)
DEF_SAFE_CONVERTI(uint8, int64)

DEF_SAFE_CONVERTU(uint16, uint32)
DEF_SAFE_CONVERTU(uint16, uint64)
DEF_SAFE_CONVERTI(uint16, int8)
DEF_SAFE_CONVERTI(uint16, int16)
DEF_SAFE_CONVERTI(uint16, int32)
DEF_SAFE_CONVERTI(uint16, int64)

DEF_SAFE_CONVERTU(uint32, uint64)
DEF_SAFE_CONVERTI(uint32, int8)
DEF_SAFE_CONVERTI(uint32, int16)
DEF_SAFE_CONVERTI(uint32, int32)
DEF_SAFE_CONVERTI(uint32, int64)

DEF_SAFE_CONVERTI(uint64, int8)
DEF_SAFE_CONVERTI(uint64, int16)
DEF_SAFE_CONVERTI(uint64, int32)
DEF_SAFE_CONVERTI(uint64, int64)


