#ifndef RENDER_SYS_INTERFACE_RENDER_SYS_INTERNAL_H
#define RENDER_SYS_INTERFACE_RENDER_SYS_INTERNAL_H

struct sge_render_sys_table;
struct sge_render_sys
{
    const struct sge_render_sys_table *vptr;
};

struct sge_render_sys_table
{
    void (*destory)(struct sge_render_sys*);
};

#endif