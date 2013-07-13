#ifndef WINDOW_WINDOW_INTERNAL_H
#define WINDOW_WINDOW_INTERNAL_H
#include "window.h"

struct sge_window_sys_table;
struct sge_window_sys
{
    const struct sge_window_sys_table * vptr;
};

struct sge_window_sys_table
{
    struct sge_window_obj* (*create_window)(struct sge_window_sys*);
    void (*main_loop)(struct sge_window_sys*);
    void (*destory)(struct sge_window_sys*);
    void (*set_handler_on_idle)(struct sge_window_sys*, on_idle);
};


struct sge_window_obj_table;
struct sge_window_obj
{
    const struct sge_window_obj_table * vptr;
};

struct sge_window_obj_table
{
    void (*show)(struct sge_window_obj*, sge_int32, sge_int32, sge_int32, sge_int32);
    void (*destroy)(struct sge_window_obj*);
    void (*set_handler_resize)(struct sge_window_obj*, on_resize);
};
#endif