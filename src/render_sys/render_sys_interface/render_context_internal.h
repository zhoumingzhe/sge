#ifndef RENDER_SYS_INTERFACE_RENDER_CONTEXT_INTERNAL_H
#define RENDER_SYS_INTERFACE_RENDER_CONTEXT_INTERNAL_H

struct sge_render_context_table;
struct sge_render_context
{
    const struct sge_render_context_table *vptr;
};

struct sge_render_context_table
{
    void (*present)(struct sge_render_context*);
    void (*destory)(struct sge_render_context*);
};

#endif