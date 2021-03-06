#include "render_headers_opengl.h"
#include "render_vertex_buffer_opengl.h"
#include "render_context_opengl.h"
#include "memory/sge_memory.h"
#include "basedefine/static_assert.h"
static GLenum opengl_vertex_buffer_usage[] =
{
    GL_STATIC_DRAW,
    GL_STATIC_DRAW,
    GL_DYNAMIC_DRAW
};

sge_static_assert(sizeof(opengl_vertex_buffer_usage) / sizeof(opengl_vertex_buffer_usage[0]), buffer_usage_equal);
static void opengl_destory_vertex_buffer(struct sge_render_vertex_buffer *buffer)
{
    VIRTUAL_CONTAINER(buffer_opengl, buffer, struct sge_render_vertex_buffer_opengl);
    sge_list_del(&buffer_opengl->vertex_list);
    glDeleteBuffers(1, &buffer_opengl->id);
    sge_free(buffer);
}
static sge_inline void upload_buffer(GLuint id, void* data, sge_uint32 size, GLenum flag)
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, data, flag);
}

static void opengl_upload_data_vertex_buffer(struct sge_render_vertex_buffer* buffer,
    void* data, sge_uint32 size)
{
    VIRTUAL_CONTAINER(buffer_opengl, buffer, struct sge_render_vertex_buffer_opengl);
    upload_buffer(buffer_opengl->id, data, size, opengl_vertex_buffer_usage[buffer_opengl->usage_flag]);
}

BEGIN_VTABLE_INSTANCE(sge_render_vertex_buffer_opengl, sge_render_vertex_buffer)
opengl_destory_vertex_buffer,
opengl_upload_data_vertex_buffer
END_VTABLE_INSTANCE


struct sge_render_vertex_buffer_opengl* create_vertex_buffer_opengl(
struct sge_render_context_opengl* context, sge_uint32 size, void* buffer,
    enum sge_vb_usage flag, sge_uint32 stride)
{
    CREATE_INSTANCE(vertex_buffer, sge_render_vertex_buffer_opengl, sge_malloc);
    sge_list_insert_after(&context->vertex_list, &vertex_buffer->vertex_list);
    vertex_buffer->context = context;
    vertex_buffer->usage_flag = flag;
    vertex_buffer->stride = stride;
    glGenBuffers(1, &vertex_buffer->id);
    if (size > 0 && buffer)
    {
        upload_buffer(vertex_buffer->id, buffer, size, opengl_vertex_buffer_usage[vertex_buffer->usage_flag]);
    }
    return vertex_buffer;
}