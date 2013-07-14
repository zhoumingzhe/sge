#include "window.h"
#include "window_internal.h"

struct sge_window_obj* sge_window_sys_create_window(struct sge_window_sys* window_sys)
{
    return window_sys->vptr->create_window(window_sys);
}

void sge_window_sys_main_loop(struct sge_window_sys* window_sys)
{
    window_sys->vptr->main_loop(window_sys);
}

void sge_window_sys_destory(struct sge_window_sys* window_sys)
{
    window_sys->vptr->destory(window_sys);
}

void sge_window_sys_set_handler_idle(struct sge_window_sys* window_sys, on_idle func)
{
    window_sys->vptr->set_handler_on_idle(window_sys, func);
}

//window functions
void sge_window_show(struct sge_window_obj* obj)
{
    obj->vptr->show(obj);
}

void sge_window_destroy(struct sge_window_obj* obj)
{
    obj->vptr->destroy(obj);
}

void sge_window_set_handler_resize(struct sge_window_obj* obj, on_resize func)
{
    obj->vptr->set_handler_resize(obj, func);
}

void* sge_window_get_native_obj(struct sge_window_obj* obj)
{
    return obj->vptr->get_native_obj(obj);
}