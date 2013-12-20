#ifndef RENDERSYS_VERTEXLAYOUT_H
#define RENDERSYS_VERTEXLAYOUT_H
#include "basedefine/types.h"
SGE_EXTERN_C_START

enum sge_vb_type
{
    sge_vb_int8;
    sge_vb_uint8;
    sge_vb_int16;
    sge_vb_uint16;
    sge_vb_int32;
    sge_vb_uint32;
    sge_vb_float16;
    sge_vb_float32;
    sge_vb_float64;
};

enum sge_vb_semantic
{
    sge_vb_position;
    sge_vb_normal;
    sge_vb_tangent;
    sge_vb_binormal;
    sge_vb_texcoord;
    sge_vb_color;
    sge_vb_blendwt;
    sge_vb_blendidx;
};


SGE_EXTERN_C_END

#endif