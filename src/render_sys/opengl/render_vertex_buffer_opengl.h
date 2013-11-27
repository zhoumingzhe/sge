#ifndef RENDERSYS_OPENGL_RENDERSYS_VERTEX_BUFFER_H
#define RENDERSYS_OPENGL_RENDERSYS_VERTEX_BUFFER_H
#include "basedefine/types.h"
#include "basedefine/list.h"
#include "render_vertex_buffer_internal.h"

struct sge_render_context_opengl;

BEGIN_IMPLEMENTATION(sge_render_vertex_buffer_opengl, sge_render_vertex_buffer)
struct sge_list_entry vertex_list;
struct sge_render_context_opengl *context;
GLuint id;
END_IMPLEMENTATION

struct sge_render_vertex_buffer_opengl* create_vertex_buffer_opengl(
struct sge_render_context_opengl* context, sge_uint32 size, void* buffer, sge_int32 flag,
    sge_uint32 stride);
#endif