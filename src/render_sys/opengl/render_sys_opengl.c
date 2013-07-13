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

static const struct sge_render_sys_table opengl_render_sys_vptr = 
{
    opengl_create_context,
    opengl_destory
};

struct sge_render_sys* create_render_sys()
{
    if(init_glew())
    {
        struct sge_render_sys_opengl* render_sys =
            (struct sge_render_sys_opengl*)sge_malloc(sizeof(struct sge_render_sys_opengl));
        render_sys->render_sys_base.vptr = &opengl_render_sys_vptr;
        return &render_sys->render_sys_base;
    }
    return 0;
}
