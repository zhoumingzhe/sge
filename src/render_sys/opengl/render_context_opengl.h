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

    sge_bool depth_test_enable;
};

BEGIN_IMPLEMENTATION(sge_render_context_opengl, sge_render_context)
    struct sge_list_entry vertex_list;
    struct sge_render_context_state_cache cache;
END_IMPLEMENTATION

void init_opengl_context(struct sge_render_context_opengl* context);

void opengl_context_clear(struct sge_render_context* context, sge_int32 mask,
                          sge_vec4f color, sge_float32 depth, sge_int32 stencil);

struct sge_render_vertex_buffer* opengl_create_vertex_buffer(
    struct sge_render_context* context, sge_uint32 size, void* buffer, enum sge_vb_usage flag,
    sge_uint32 stride);

    void opengl_enable_depth_test(struct sge_render_context* context, sge_bool size);

void opengl_draw(struct sge_render_context* context, enum sge_primitive_type type, sge_int32 start, sge_int32 count);

struct sge_render_vertex_layout* opengl_create_vertex_layout(struct sge_render_context* context,
    const struct sge_render_vertex_buffer * buffers, sge_uint32 buffer_size,
    const struct sge_vb_layout *layouts, sge_uint32 layout_size);

#endif