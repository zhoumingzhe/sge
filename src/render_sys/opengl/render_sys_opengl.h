#ifndef RENDERSYS_OPENGL_RENDERSYS_OPENGL_H
#define RENDERSYS_OPENGL_RENDERSYS_OPENGL_H
#include "basedefine/types.h"
#include "render_sys_internal.h"

BEGIN_IMPLEMENTATION(sge_render_sys_opengl, sge_render_sys)
    struct sge_render_sys render_sys_base;
END_IMPLEMENTATION

__declspec(dllexport) struct sge_render_sys* create_render_sys();
#endif