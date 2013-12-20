#ifndef RENDER_SYS_INTERFACE_RENDER_CONTEXT_INTERNAL_H
#define RENDER_SYS_INTERFACE_RENDER_CONTEXT_INTERNAL_H
#include "render_context.h"
#include "basedefine/polymorphic.h"

BEGIN_VTABLE(sge_render_context)
    void (*present)(struct sge_render_context*);
    void (*destory)(struct sge_render_context*);
    void (*clear)(struct sge_render_context*, sge_int32, sge_vec4f, sge_float32, sge_int32);
    struct sge_render_vertex_buffer* (*create_vertex_buffer)(struct sge_render_context*, sge_uint32, void*, enum sge_vb_usage, sge_uint32);
    void (*enable_depth_test)(struct sge_render_context*, sge_bool);
    void (*draw)(struct sge_render_context*, enum sge_primitive_type, sge_int32, sge_int32);
    struct sge_render_vertex_layout* (*create_vertex_layout)(struct sge_render_context*, const struct sge_render_vertex_buffer*, sge_uint32, const struct sge_vb_layout*, sge_uint32);
END_VTABLE(sge_render_context)

#endif