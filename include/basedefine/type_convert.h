#ifndef BASEDEFINE_TYPE_CONVERT_H
#define BASEDEFINE_TYPE_CONVERT_H
#include "types.h"

#ifdef __cplusplus

template <typename to, typename from>
to sge_safe_convert(from f);

#endif
SGE_EXTERN_C_START
#define DECL_SAFE_CONVERT(to, from)\
to sge_safe_convert_##from##_to_##to(from f);
DECL_SAFE_CONVERT(sge_int8, sge_int16)
DECL_SAFE_CONVERT(sge_int8, sge_int32)
DECL_SAFE_CONVERT(sge_int8, sge_int64)
DECL_SAFE_CONVERT(sge_int8, sge_uint8)
DECL_SAFE_CONVERT(sge_int8, sge_uint16)
DECL_SAFE_CONVERT(sge_int8, sge_uint32)
DECL_SAFE_CONVERT(sge_int8, sge_uint64)

DECL_SAFE_CONVERT(sge_int16, sge_int32)
DECL_SAFE_CONVERT(sge_int16, sge_int64)
DECL_SAFE_CONVERT(sge_int16, sge_uint16)
DECL_SAFE_CONVERT(sge_int16, sge_uint32)
DECL_SAFE_CONVERT(sge_int16, sge_uint64)

DECL_SAFE_CONVERT(sge_int32, sge_int64)
DECL_SAFE_CONVERT(sge_int32, sge_uint32)
DECL_SAFE_CONVERT(sge_int32, sge_uint64)

DECL_SAFE_CONVERT(sge_int64, sge_uint64)

DECL_SAFE_CONVERT(sge_uint8, sge_uint16)
DECL_SAFE_CONVERT(sge_uint8, sge_uint32)
DECL_SAFE_CONVERT(sge_uint8, sge_uint64)
DECL_SAFE_CONVERT(sge_uint8, sge_int8)
DECL_SAFE_CONVERT(sge_uint8, sge_int16)
DECL_SAFE_CONVERT(sge_uint8, sge_int32)
DECL_SAFE_CONVERT(sge_uint8, sge_int64)

DECL_SAFE_CONVERT(sge_uint16, sge_uint32)
DECL_SAFE_CONVERT(sge_uint16, sge_uint64)
DECL_SAFE_CONVERT(sge_uint16, sge_int8)
DECL_SAFE_CONVERT(sge_uint16, sge_int16)
DECL_SAFE_CONVERT(sge_uint16, sge_int32)
DECL_SAFE_CONVERT(sge_uint16, sge_int64)

DECL_SAFE_CONVERT(sge_uint32, sge_uint64)
DECL_SAFE_CONVERT(sge_uint32, sge_int8)
DECL_SAFE_CONVERT(sge_uint32, sge_int16)
DECL_SAFE_CONVERT(sge_uint32, sge_int32)
DECL_SAFE_CONVERT(sge_uint32, sge_int64)

DECL_SAFE_CONVERT(sge_uint64, sge_int8)
DECL_SAFE_CONVERT(sge_uint64, sge_int16)
DECL_SAFE_CONVERT(sge_uint64, sge_int32)
DECL_SAFE_CONVERT(sge_uint64, sge_int64)

SGE_EXTERN_C_END
#endif
