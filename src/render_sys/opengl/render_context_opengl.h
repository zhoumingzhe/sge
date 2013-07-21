#ifndef RENDERSYS_OPENGL_RENDERSYS_OPENGL_H
#define RENDERSYS_OPENGL_RENDERSYS_OPENGL_H
#include "basedefine/types.h"
#include "render_context_internal.h"

struct sge_render_context_opengl
{
    struct sge_render_context render_context_base;

    //internal cache
    sge_vec4f clear_color;
    sge_float32 clear_depth;
    sge_int32 clear_stencil;
};

void init_opengl_context(struct sge_render_context_opengl* context);

void opengl_context_clear(struct sge_render_context* context, sge_int32 mask,
                          sge_vec4f color, sge_float32 depth, sge_int32 stencil);

#endif