#ifndef RENDERSYS_RENDERCONTEXT_H
#define RENDERSYS_RENDERCONTEXT_H
#include "basedefine/types.h"
#include "mathlib/vector.h"


SGE_EXTERN_C_START

struct sge_render_context;
struct sge_render_vertex_buffer;
struct sge_render_vertex_layout;

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

void sge_render_context_enable_depth_test(struct sge_render_context* context, sge_bool enable);

enum sge_primitive_type
{
    sge_pt_triangle,
    sge_pt_triangle_fan,
    sge_pt_triangle_strip,
    sge_pt_end
};
void sge_render_context_draw(struct sge_render_context* context, enum sge_primitive_type type,
    sge_int32 start, sge_int32 count);

enum sge_vb_type;
enum sge_vb_semantic;

struct sge_vb_layout
{
    sge_int32 vb_index;
    enum sge_vb_type type;
    sge_int32 count;
    enum sge_vb_semantic semantic;
    sge_int32 semantic_index;
};

struct sge_render_vertex_layout* sge_render_context_create_vertex_layout(struct sge_render_context* context,
    const struct sge_render_vertex_buffer * buffers, sge_uint32 buffer_size,
    const struct sge_vb_layout *layouts, sge_uint32 layout_size);


SGE_EXTERN_C_END
#endif