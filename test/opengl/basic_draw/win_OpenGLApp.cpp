#include "windows.h"
#include "window/window.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int iShow)
{

    struct sge_window_sys* window_sys = sge_window_sys_create_win32();
    //todo: init opengl enviroment, register idle function
    struct sge_window_obj* obj = sge_window_sys_create_window(window_sys);

    //todo: init opengl on window and register resize function
    sge_window_show(obj, 0, 0, 800, 600);
    sge_window_sys_main_loop(window_sys);

    //todo: destroy opengll on window
    sge_window_destroy(obj);

    //todo: destory opengl enviroment
    sge_window_sys_destory(window_sys);
    return 0;
}

