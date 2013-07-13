#include <windows.h>
#include "render_sys.h"
#include "render_sys_internal.h"

typedef struct sge_render_sys* (*create_func)();
static struct sge_render_sys* create_render_sys_by_name(char* name)
{
    create_func func;
    HMODULE hmodule = LoadLibraryA(name);
    if(!hmodule)
        return 0;
    func = (create_func)GetProcAddress(hmodule, "create_render_sys");
    return func();
}

struct sge_render_sys* sge_create_render_sys(struct sge_window_sys* window_sys,
    enum sge_render_sys_type render_sys_type)
{
    switch (render_sys_type)
    {
    case sge_rs_opengl:
        return create_render_sys_by_name("render_sys_opengl");
        break;
    default:
        return 0;
        break;
    }
}

struct sge_render_context* sge_create_render_context(
                    struct sge_render_sys* render_sys,
                    struct sge_window_obj* window_obj)
{
    return render_sys->vptr->create_render_context(render_sys, window_obj);
}
void sge_render_sys_destroy(struct sge_render_sys* render_sys)
{
    render_sys->vptr->destory(render_sys);
}