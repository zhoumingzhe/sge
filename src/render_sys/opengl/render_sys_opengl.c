#include "render_sys_internal.h"
#include "render_sys_opengl.h"
#include "platform_support.h"
#include "memory/sge_memory.h"

void opengl_destory(struct sge_render_sys* render_sys)
{
    sge_free(render_sys);
}

struct sge_render_context* opengl_create_context(struct sge_render_sys* render_sys,
                    struct sge_window_obj* window_obj)
{
    return create_context(render_sys, window_obj);
}

BEGIN_VTABLE_INSTANCE(sge_render_sys_opengl, sge_render_sys)
    opengl_create_context,
    opengl_destory
END_VTABLE_INSTANCE

struct sge_render_sys* create_render_sys()
{
    if(init_glew())
    {
        CREATE_INSTANCE(render_sys, sge_render_sys_opengl, sge_malloc);
        return GET_INTERFACE(render_sys);
    }
    return 0;
}
