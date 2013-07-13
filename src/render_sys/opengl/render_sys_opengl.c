#include "render_sys_internal.h"
#include "render_sys_opengl.h"
#include "memory/sge_memory.h"

void opengl_destory(struct sge_render_sys* render_sys)
{
    sge_free(render_sys);
}
static const struct sge_render_sys_table opengl_render_sys_vptr = 
{
    opengl_destory
};

struct sge_render_sys* create_render_sys()
{
    if(init_glew())
    {
        struct sge_render_sys_opengl* render_sys =
            (struct sge_render_sys_opengl*)sge_malloc(sizeof(struct sge_render_sys_opengl));
        render_sys->render_sys.vptr = &opengl_render_sys_vptr;
        return &render_sys->render_sys;
    }
    return 0;
}
