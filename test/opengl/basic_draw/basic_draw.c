#include "windows.h"
#include "window/window.h"
#include "render_sys/render_sys.h"
#include "render_sys/render_context.h"
#include <crtdbg.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int iShow)
{

    int i = _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    struct sge_window_sys* window_sys = sge_window_sys_create_win32();
    struct sge_render_sys* render_sys = sge_create_render_sys(window_sys, sge_rs_opengl);
    struct sge_window_obj* obj = sge_window_sys_create_window(window_sys);

    struct sge_render_context* context = sge_create_render_context(render_sys, obj);

    sge_window_show(obj);
    sge_window_sys_main_loop(window_sys);

    sge_render_context_destroy(context);
    sge_window_destroy(obj);

    sge_render_sys_destroy(render_sys);
    sge_window_sys_destory(window_sys);
    UNUSED(i);
    return 0;
}

