#ifndef RENDERSYS_VERTEXBUFFER_H
#define RENDERSYS_VERTEXBUFFER_H
#include "basedefine/platform.h"
SGE_EXTERN_C_START

struct sge_render_vertex_buffer;
void sge_render_vertex_buffer_destroy(struct sge_render_vertex_buffer* buffer);
SGE_EXTERN_C_END

#endif