
#include "render_vertex_buffer.h"
#include "render_vertex_buffer_internal.h"
void sge_render_vertex_buffer_destroy(struct sge_render_vertex_buffer* buffer)
{
    VTABLE_CALL(buffer, destroy)(buffer);
}

void sge_render_vertex_buffer_upload_data(struct sge_render_vertex_buffer* buffer,
    void* data, sge_uint32 size)
{
    VTABLE_CALL(buffer, upload_data)(buffer, data,size);
}