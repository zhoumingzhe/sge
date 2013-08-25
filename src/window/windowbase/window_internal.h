#ifndef WINDOW_WINDOW_INTERNAL_H
#define WINDOW_WINDOW_INTERNAL_H
#include "window.h"
#include <basedefine/polymorphic.h>

BEGIN_VTABLE(sge_window_sys)
    struct sge_window_obj* (*create_window)(struct sge_window_sys*);
    void (*main_loop)(struct sge_window_sys*);
    void (*destory)(struct sge_window_sys*);
    void (*set_handler_on_idle)(struct sge_window_sys*, on_idle);
END_VTABLE(sge_window_sys)

BEGIN_VTABLE(sge_window_obj)
    void (*show)(struct sge_window_obj*);
    void (*destroy)(struct sge_window_obj*);
    void (*set_handler_resize)(struct sge_window_obj*, on_resize);
    void* (*get_native_obj)(struct sge_window_obj*);
END_VTABLE(sge_window_obj)
#endif