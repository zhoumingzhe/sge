#ifndef WINDOW_WINDOW_H
#define WINDOW_WINDOW_H
#include "basedefine/types.h"
SGE_EXTERN_C_START
struct sge_window_sys;
struct sge_window_obj;

enum sge_window_type
{
    sge_window_win32
};

//window system interfaces
struct sge_window_sys* sge_window_sys_create_win32();
struct sge_window_obj* sge_window_sys_create_window(struct sge_window_sys* window_sys);
void sge_window_sys_main_loop(struct sge_window_sys* window_sys);
void sge_window_sys_destory(struct sge_window_sys* window_sys);

//window system handlers
typedef void (*on_idle)(struct sge_window_sys* window_sys);
void sge_window_sys_set_handler_idle(struct sge_window_sys* window_sys);

//window functions
void sge_window_show(struct sge_window_obj* obj);
void sge_window_destroy(struct sge_window_obj* obj);
void* sge_window_get_native_obj(struct sge_window_obj* obj);

//window handlers
typedef void (*on_resize)(struct sge_window_obj* obj, sge_int32, sge_int32);
void sge_window_set_handler_resize(struct sge_window_obj* obj, on_resize func);

SGE_EXTERN_C_END
#endif
