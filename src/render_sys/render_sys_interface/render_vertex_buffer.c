
#include "render_vertex_buffer.h"
#include "render_vertex_buffer_internal.h"
void sge_render_vertex_buffer_destroy(struct sge_render_vertex_buffer* buffer)
{
    VTABLE_CALL(buffer, destroy)(buffer);
}