#include "render_context.h"
#include "render_context_internal.h"

void sge_render_context_present(struct sge_render_context* render_context)
{
    render_context->vptr->present(render_context);
}

void sge_render_context_destroy(struct sge_render_context* render_context)
{
    render_context->vptr->destory(render_context);
}

void sge_render_context_clear(struct sge_render_context* render_context,
     sge_int32 mask, sge_vec4f color, sge_float32 depth, sge_int32 stencil)
{
    render_context->vptr->clear(render_context, mask, color, depth, stencil);
}

struct sge_render_veretex_buffer* sge_render_context_create_vertex_buffer(struct sge_render_context* render_context)
{
    return render_context->vptr->create_vertex_buffer(render_context);
}
