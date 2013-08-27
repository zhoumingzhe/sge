#ifndef RENDER_SYS_INTERFACE_RENDER_SYS_INTERNAL_H
#define RENDER_SYS_INTERFACE_RENDER_SYS_INTERNAL_H
#include "render_sys.h"
#include "basedefine/polymorphic.h"
struct sge_window_obj;

BEGIN_VTABLE(sge_render_sys)
    struct sge_render_context* (*create_render_context)(struct sge_render_sys*, struct sge_window_obj*);
    void (*destory)(struct sge_render_sys*);
END_VTABLE(sge_render_sys)

#endif