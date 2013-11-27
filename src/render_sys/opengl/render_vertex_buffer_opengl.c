#include "render_headers_opengl.h"
#include "render_vertex_buffer_opengl.h"
#include "render_context_opengl.h"
#include "memory/sge_memory.h"

void opengl_destory_vertex_buffer(struct sge_render_vertex_buffer *buffer)
{
    VIRTUAL_CONTAINER(buffer_opengl, buffer, struct sge_render_vertex_buffer_opengl);
    sge_list_del(&buffer_opengl->vertex_list);
    glDeleteBuffers(1, &buffer_opengl->id);
    sge_free(buffer);
}

BEGIN_VTABLE_INSTANCE(sge_render_vertex_buffer_opengl, sge_render_vertex_buffer)
opengl_destory_vertex_buffer
END_VTABLE_INSTANCE

static GLenum opengl_vertex_buffer_usage[] =
{
    GL_STATIC_DRAW,
    GL_STATIC_DRAW,
    GL_DYNAMIC_DRAW
};

struct sge_render_vertex_buffer_opengl* create_vertex_buffer_opengl(
struct sge_render_context_opengl* context, sge_uint32 size, void* buffer, enum sge_vb_usage flag,
    sge_uint32 stride)
{
    CREATE_INSTANCE(vertex_buffer, sge_render_vertex_buffer_opengl, sge_malloc);
    sge_list_insert_after(&context->vertex_list, &vertex_buffer->vertex_list);
    vertex_buffer->context = context;
    glGenBuffers(1, &vertex_buffer->id);
    glBindBuffer(vertex_buffer->id, GL_ARRAY_BUFFER);
    glBufferData(vertex_buffer->id, size, buffer, opengl_vertex_buffer_usage[flag]);
    return vertex_buffer;
}