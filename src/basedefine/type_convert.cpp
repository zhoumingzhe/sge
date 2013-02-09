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
template to sge_safe_convert<to, from>(from f);\
to sge_safe_convert_##from##_to_##to(from f)\
{\
    return sge_safe_convert<to>(f);\
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

DEF_SAFE_CONVERT(sge_int8, sge_int16)
DEF_SAFE_CONVERT(sge_int8, sge_int32)
DEF_SAFE_CONVERT(sge_int8, sge_int64)
DEF_SAFE_CONVERT(sge_int8, sge_uint8)
DEF_SAFE_CONVERT(sge_int8, sge_uint16)
DEF_SAFE_CONVERT(sge_int8, sge_uint32)
DEF_SAFE_CONVERT(sge_int8, sge_uint64)

DEF_SAFE_CONVERT(sge_int16, sge_int32)
DEF_SAFE_CONVERT(sge_int16, sge_int64)
DEF_SAFE_CONVERT(sge_int16, sge_uint16)
DEF_SAFE_CONVERT(sge_int16, sge_uint32)
DEF_SAFE_CONVERT(sge_int16, sge_uint64)

DEF_SAFE_CONVERT(sge_int32, sge_int64)
DEF_SAFE_CONVERT(sge_int32, sge_uint32)
DEF_SAFE_CONVERT(sge_int32, sge_uint64)

DEF_SAFE_CONVERT(sge_int64, sge_uint64)

DEF_SAFE_CONVERT(sge_uint8, sge_uint16)
DEF_SAFE_CONVERT(sge_uint8, sge_uint32)
DEF_SAFE_CONVERT(sge_uint8, sge_uint64)
DEF_SAFE_CONVERT(sge_uint8, sge_int8)
DEF_SAFE_CONVERT(sge_uint8, sge_int16)
DEF_SAFE_CONVERT(sge_uint8, sge_int32)
DEF_SAFE_CONVERT(sge_uint8, sge_int64)

DEF_SAFE_CONVERT(sge_uint16, sge_uint32)
DEF_SAFE_CONVERT(sge_uint16, sge_uint64)
DEF_SAFE_CONVERT(sge_uint16, sge_int8)
DEF_SAFE_CONVERT(sge_uint16, sge_int16)
DEF_SAFE_CONVERT(sge_uint16, sge_int32)
DEF_SAFE_CONVERT(sge_uint16, sge_int64)

DEF_SAFE_CONVERT(sge_uint32, sge_uint64)
DEF_SAFE_CONVERT(sge_uint32, sge_int8)
DEF_SAFE_CONVERT(sge_uint32, sge_int16)
DEF_SAFE_CONVERT(sge_uint32, sge_int32)
DEF_SAFE_CONVERT(sge_uint32, sge_int64)

DEF_SAFE_CONVERT(sge_uint64, sge_int8)
DEF_SAFE_CONVERT(sge_uint64, sge_int16)
DEF_SAFE_CONVERT(sge_uint64, sge_int32)
DEF_SAFE_CONVERT(sge_uint64, sge_int64)


