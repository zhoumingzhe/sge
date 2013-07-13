#ifndef RENDERSYS_OPENGL_RENDERSYS_OPENGL_H
#define RENDERSYS_OPENGL_RENDERSYS_OPENGL_H
#include "basedefine/types.h"
#include "render_sys_internal.h"
sge_bool init_glew();
struct sge_render_sys_opengl
{
    struct sge_render_sys render_sys;
};

__declspec(dllexport) struct sge_render_sys* create_render_sys();
#endif