#include "render_vertex_buffer_opengl.h"
#include "memory/sge_memory.h"

void opengl_destory_vertex_buffer(struct sge_render_vertex_buffer *buffer)
{
    VIRTUAL_CONTAINER(buffer_opengl, buffer, struct sge_render_vertex_buffer_opengl);
    sge_list_del(&buffer_opengl->vertex_list);
    sge_free(buffer);
}

BEGIN_VTABLE_INSTANCE(sge_render_vertex_buffer_opengl, sge_render_vertex_buffer)
opengl_destory_vertex_buffer
END_VTABLE_INSTANCE

struct sge_render_vertex_buffer_opengl* create_vertex_buffer_opengl()
{
    CREATE_INSTANCE(vertex_buffer, sge_render_vertex_buffer_opengl, sge_malloc);
	return vertex_buffer;
}