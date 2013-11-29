#ifndef RENDER_SYS_INTERFACE_RENDER_VERTEX_BUFFER_INTERNAL_H
#define RENDER_SYS_INTERFACE_RENDER_VERTEX_BUFFER_INTERNAL_H
#include "render_vertex_buffer.h"
#include "basedefine/polymorphic.h"

BEGIN_VTABLE(sge_render_vertex_buffer)
    void(*destroy)(struct sge_render_vertex_buffer*);
    void(*upload_data)(struct sge_render_vertex_buffer*, void *, sge_uint32);
END_VTABLE(sge_render_vertex_buffer)

#endif