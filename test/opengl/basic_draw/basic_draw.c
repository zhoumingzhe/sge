#include "windows.h"
#include "window/window.h"
#include "render_sys/render_sys.h"
#include "render_sys/render_context.h"
#include "mathlib/matrix.h"
#include <crtdbg.h>
#define GLEW_STATIC
#include "GL/glew.h"


void initScene();
void renderScene();
void releaseScene();

struct sge_render_context* g_render_context;
sge_mat44f mProjection;
void RESIZE(struct sge_window_obj* obj, sge_int32 width, sge_int32 height)
{
    glViewport(0, 0, width, height);
    mProjection = sge_mat44f_perspective_rh_gl(0.002f*(float)(width)/(float)(height), 0.002f, 0.001f, 1000.0f);
}

void IDLE(struct sge_window_sys* window_sys)
{
    renderScene();
    sge_render_context_present(g_render_context);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int iShow)
{

    int i = _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    struct sge_window_sys* window_sys = sge_window_sys_create_win32();
    struct sge_render_sys* render_sys = sge_create_render_sys(window_sys, sge_rs_opengl);
    struct sge_window_obj* obj = sge_window_sys_create_window(window_sys);
    struct sge_render_context* context = sge_create_render_context(render_sys, obj);
    g_render_context = context;
    initScene();
    sge_window_set_handler_resize(obj, RESIZE);

    sge_window_show(obj);
    sge_window_sys_set_handler_idle(window_sys, IDLE);
    sge_window_sys_main_loop(window_sys);

    sge_render_context_destroy(context);
    sge_window_destroy(obj);

    releaseScene();
    sge_render_sys_destroy(render_sys);
    sge_window_sys_destory(window_sys);
    UNUSED(i);
    return 0;
}

