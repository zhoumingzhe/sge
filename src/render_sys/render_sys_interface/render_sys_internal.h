#ifndef RENDER_SYS_INTERFACE_RENDER_SYS_INTERNAL_H
#define RENDER_SYS_INTERFACE_RENDER_SYS_INTERNAL_H

struct sge_window_sys;
struct sge_window_obj;

struct sge_render_sys_table;
struct sge_render_sys
{
    const struct sge_render_sys_table *vptr;
};

struct sge_render_sys_table
{
    struct sge_render_context* (*create_render_context)(struct sge_render_sys*, struct sge_window_obj*);
    void (*destory)(struct sge_render_sys*);
};

#endif