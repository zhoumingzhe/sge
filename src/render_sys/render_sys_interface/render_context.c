#include "render_context.h"
#include "render_context_internal.h"

void sge_render_context_destroy(struct sge_render_context* render_context)
{
    render_context->vptr->destory(render_context);
}