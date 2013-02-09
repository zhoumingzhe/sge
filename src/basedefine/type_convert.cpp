#include <assert.h>
#include "type_convert.h"
template<typename t>
t sge_get_max();

template<typename t>
t sge_get_min();

template<typename to, typename from>
to sge_safe_convert(from f)
{
    to to_min = sge_get_min<to>();
    to to_max = sge_get_max<to>();
    if(f<0)
        assert(to_min<0&&f>=to_min);
    else
        assert(f<=to_max);
    return (to)f;
}

#define DEF_SAFE_CONVERT(to, from)\
template sge_##to sge_safe_convert<sge_##to, sge_##from>(sge_##from f);\
sge_##to sge_safe_convert_##from##_to_##to(sge_##from f)\
{\
    return sge_safe_convert<sge_##to>(f);\
}

#define DEF_GET_MAX(type) template<> type sge_get_max<type>(){ return (type##_max);}
#define DEF_GET_MIN(type) template<> type sge_get_min<type>(){ return (type##_min);}
#define DEF_GET_MIN_0(type) template<> type sge_get_min<type>() {return 0;}

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
DEF_GET_MIN(sge_int64)

DEF_GET_MIN_0(sge_uint8)
DEF_GET_MIN_0(sge_uint16)
DEF_GET_MIN_0(sge_uint32)
DEF_GET_MIN_0(sge_uint64)

DEF_SAFE_CONVERT(int8, int16)
DEF_SAFE_CONVERT(int8, int32)
DEF_SAFE_CONVERT(int8, int64)
DEF_SAFE_CONVERT(int8, uint8)
DEF_SAFE_CONVERT(int8, uint16)
DEF_SAFE_CONVERT(int8, uint32)
DEF_SAFE_CONVERT(int8, uint64)

DEF_SAFE_CONVERT(int16, int32)
DEF_SAFE_CONVERT(int16, int64)
DEF_SAFE_CONVERT(int16, uint16)
DEF_SAFE_CONVERT(int16, uint32)
DEF_SAFE_CONVERT(int16, uint64)

DEF_SAFE_CONVERT(int32, int64)
DEF_SAFE_CONVERT(int32, uint32)
DEF_SAFE_CONVERT(int32, uint64)

DEF_SAFE_CONVERT(int64, uint64)

DEF_SAFE_CONVERT(uint8, uint16)
DEF_SAFE_CONVERT(uint8, uint32)
DEF_SAFE_CONVERT(uint8, uint64)
DEF_SAFE_CONVERT(uint8, int8)
DEF_SAFE_CONVERT(uint8, int16)
DEF_SAFE_CONVERT(uint8, int32)
DEF_SAFE_CONVERT(uint8, int64)

DEF_SAFE_CONVERT(uint16, uint32)
DEF_SAFE_CONVERT(uint16, uint64)
DEF_SAFE_CONVERT(uint16, int8)
DEF_SAFE_CONVERT(uint16, int16)
DEF_SAFE_CONVERT(uint16, int32)
DEF_SAFE_CONVERT(uint16, int64)

DEF_SAFE_CONVERT(uint32, uint64)
DEF_SAFE_CONVERT(uint32, int8)
DEF_SAFE_CONVERT(uint32, int16)
DEF_SAFE_CONVERT(uint32, int32)
DEF_SAFE_CONVERT(uint32, int64)

DEF_SAFE_CONVERT(uint64, int8)
DEF_SAFE_CONVERT(uint64, int16)
DEF_SAFE_CONVERT(uint64, int32)
DEF_SAFE_CONVERT(uint64, int64)


