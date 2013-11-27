#ifndef RENDERSYS_VERTEXBUFFER_H
#define RENDERSYS_VERTEXBUFFER_H
#include "basedefine/platform.h"
SGE_EXTERN_C_START
enum sge_vb_usage
{
    sge_vb_immutable,       //read only both by cpu and gpu initialize at creation
    sge_vb_static,          //read write by cpu and gpu
    sge_vb_dynamic          //cpu write, gpu read
};

struct sge_render_vertex_buffer;
void sge_render_vertex_buffer_destroy(struct sge_render_vertex_buffer* buffer);
SGE_EXTERN_C_END

#endif