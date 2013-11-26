#ifndef RENDERSYS_OPENGL_CONTEXT_H
#define RENDERSYS_OPENGL_CONTEXT_H
#include "basedefine/types.h"
#include "basedefine/list.h"
#include "render_context_internal.h"

//internal cache
struct sge_render_context_state_cache
{
    sge_vec4f clear_color;
    sge_float32 clear_depth;
    sge_int32 clear_stencil;
};

BEGIN_IMPLEMENTATION(sge_render_context_opengl, sge_render_context)
    struct sge_render_context_state_cache cache;
    struct sge_list_entry vertex_list;
END_IMPLEMENTATION

void init_opengl_context(struct sge_render_context_opengl* context);

void opengl_context_clear(struct sge_render_context* context, sge_int32 mask,
                          sge_vec4f color, sge_float32 depth, sge_int32 stencil);

struct sge_render_vertex_buffer* opengl_create_vertex_buffer(
struct sge_render_context* context, sge_uint32 size, void* buffer, sge_int32 flag,
    sge_uint32 stride);
#endif