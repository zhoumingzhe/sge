#include "render_context_internal.h"

void sge_render_context_present(struct sge_render_context* render_context)
{
    VTABLE_CALL(render_context, present)(render_context);
}

void sge_render_context_destroy(struct sge_render_context* render_context)
{
    VTABLE_CALL(render_context, destory)(render_context);
}

void sge_render_context_clear(struct sge_render_context* render_context,
     sge_int32 mask, sge_vec4f color, sge_float32 depth, sge_int32 stencil)
{
    VTABLE_CALL(render_context, clear)(render_context, mask, color, depth, stencil);
}

struct sge_render_vertex_buffer* sge_render_context_create_vertex_buffer(
    struct sge_render_context* context, sge_uint32 size, void* buffer, enum sge_vb_usage flag,
    sge_uint32 stride)
{
    return VTABLE_CALL(context, create_vertex_buffer)(context, size, buffer, flag, stride);
}

void sge_render_context_enable_depth_test(struct sge_render_context* context, sge_bool enable)
{
    VTABLE_CALL(context, enable_depth_test)(context, enable);
}

void sge_render_context_draw(struct sge_render_context* context, enum sge_primitive_type type, sge_int32 start, sge_int32 count)
{
    VTABLE_CALL(context, draw)(context, type, start, count);
}

struct sge_render_vertex_layout* sge_render_context_create_vertex_layout(struct sge_render_context* context,
    const struct sge_render_vertex_buffer * buffers, sge_uint32 buffer_size,
    const struct sge_vb_layout *layouts, sge_uint32 layout_size)
{
    return VTABLE_CALL(context, create_vertex_layout)(context, buffers, buffer_size, layouts, layout_size);
}