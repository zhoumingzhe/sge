#ifndef RENDERSYS_RENDERCONTEXT_H
#define RENDERSYS_RENDERCONTEXT_H
#include "basedefine/types.h"
#include "mathlib/vector.h"


SGE_EXTERN_C_START

struct sge_render_context;
struct sge_render_vertex_buffer;

void sge_render_context_present(struct sge_render_context*);
void sge_render_context_destroy(struct sge_render_context*);

enum sge_render_context_clear_mask
{
    clear_color = 1,
    clear_depth = 2,
    clear_stencil = 4
};
void sge_render_context_clear(struct sge_render_context*, sge_int32 mask,
                              sge_vec4f color, sge_float32 depth, sge_int32 stencil);

enum sge_vb_usage;

struct sge_render_vertex_buffer* sge_render_context_create_vertex_buffer(
struct sge_render_context* context, sge_uint32 size, void* buffer, enum sge_vb_usage flag,
    sge_uint32 stride);
SGE_EXTERN_C_END
#endif