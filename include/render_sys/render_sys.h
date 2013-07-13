#ifndef RENDERSYS_RENDERSYS_H
#define RENDERSYS_RENDERSYS_H
#include "basedefine/platform.h"
struct sge_render_sys;
struct sge_render_context;

struct sge_window_sys;
struct sge_window_obj;
SGE_EXTERN_C_START
enum sge_render_sys_type
{
    sge_rs_opengl
};

struct sge_render_sys* sge_create_render_sys(struct sge_window_sys*, enum sge_render_sys_type);
struct sge_render_context* sge_create_render_context(struct sge_render_sys*, struct sge_window_obj*);
void sge_render_sys_destroy(struct sge_render_sys*);

SGE_EXTERN_C_START
#endif