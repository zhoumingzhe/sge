#include <windows.h>
#include "basedefine/runtime_assert.h"
#include "basedefine/utility.h"
#include "window_internal.h"
#include "memory/sge_memory.h"

BEGIN_IMPLEMENTATION(sge_window_sys_win32, sge_window_sys)
    on_idle idle_func;
END_IMPLEMENTATION

BEGIN_IMPLEMENTATION(sge_window_obj_win32, sge_window_obj)
    HWND hwnd;
    on_resize resize_func;
END_IMPLEMENTATION

void win32_show(struct sge_window_obj* obj)
{
    VIRTUAL_CONTAINER(win32_obj, obj, struct sge_window_obj_win32);

    ShowWindow(win32_obj->hwnd, SW_SHOW);
    UpdateWindow(win32_obj->hwnd);
}

void win32_obj_destroy(struct sge_window_obj* obj)
{
    VIRTUAL_CONTAINER(win32_obj, obj, struct sge_window_obj_win32);

    sge_runtime_assert(!!win32_obj->hwnd);
    DestroyWindow(win32_obj->hwnd);
    sge_free(win32_obj);
}

void win32_set_handler_resize(struct sge_window_obj* obj, on_resize func)
{
    VIRTUAL_CONTAINER(win32_obj, obj, struct sge_window_obj_win32);
    win32_obj->resize_func = func;
}

void* win32_get_native_obj(struct sge_window_obj* obj)
{
    VIRTUAL_CONTAINER(win32_obj, obj, struct sge_window_obj_win32);
    return win32_obj->hwnd;
}
BEGIN_VTABLE_INSTANCE(sge_window_obj_win32, sge_window_obj)
    win32_show,
    win32_obj_destroy,
    win32_set_handler_resize,
    win32_get_native_obj
END_VTABLE_INSTANCE

static struct sge_window_obj* win32_create_window(struct sge_window_sys* window_sys, on_resize func)
{
    CREATE_INSTANCE(ret, sge_window_obj_win32, sge_malloc);
    ret->hwnd = 0;
    ret->resize_func = func;

    if(MessageBox(NULL, "Would you like to run in fullscreen?", "Fullscreen", MB_ICONQUESTION | MB_YESNO) == IDYES)
    {
        DEVMODE dmSettings = {0};
        EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmSettings); // Get current display settings

        ret->hwnd = CreateWindowEx(0, "basic_draw", "basic_draw", WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // This is the commonly used style for fullscreen
            0, 0, dmSettings.dmPelsWidth, dmSettings.dmPelsHeight, NULL,
            NULL, 0, ret);
    }
    else
    {
        ret->hwnd = CreateWindowEx(0, "basic_draw", "basic_draw", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
            0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
            NULL, 0, ret);
    }

    return GET_INTERFACE(ret);
}

static void win32_loop(struct sge_window_sys* window_sys)
{
    VIRTUAL_CONTAINER(win32_obj, window_sys, struct sge_window_sys_win32);
    MSG msg;
    for(;;)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)break; // If the message was WM_QUIT then exit application
            else
            {
                TranslateMessage(&msg); // Otherwise send message to appropriate window
                DispatchMessage(&msg);
            }
        }
        else
        {
            if(win32_obj->idle_func)
                win32_obj->idle_func(window_sys);
        }
    }
}

static void win32_destory(struct sge_window_sys* window_sys)
{
    VIRTUAL_CONTAINER(ret, window_sys, struct sge_window_sys_win32);
    UnregisterClass("basic_draw", 0);
    sge_free(ret);
}

static void win32_set_on_idle(struct sge_window_sys* window_sys, on_idle func)
{
    VIRTUAL_CONTAINER(ret, window_sys, struct sge_window_sys_win32);
    ret->idle_func = func;
}

BEGIN_VTABLE_INSTANCE(sge_window_sys_win32, sge_window_sys)
    win32_create_window,
    win32_loop,
    win32_destory,
    win32_set_on_idle
END_VTABLE_INSTANCE

LRESULT CALLBACK msgHandlerMain(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    struct sge_window_obj_win32* obj_win32 = 0;
    if (uiMsg == WM_CREATE)
    {
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)(((LPCREATESTRUCT)lParam)->lpCreateParams));
        return 0;
    }


    obj_win32 = (struct sge_window_obj_win32*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    if (!obj_win32)
        return DefWindowProc(hWnd, uiMsg, wParam, lParam);

    switch(uiMsg)
    {

    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_SIZE:
        if(obj_win32->resize_func)
            obj_win32->resize_func(GET_INTERFACE(obj_win32), LOWORD(lParam), HIWORD(lParam));
        break;

    default:
        return DefWindowProc(hWnd, uiMsg, wParam, lParam);
    }
    return 0;
}

struct sge_window_sys* sge_window_sys_create_win32()
{
    WNDCLASSEX wcex;
    CREATE_INSTANCE(ret, sge_window_sys_win32, sge_malloc);

    memset(&wcex, 0, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.hIcon = LoadIcon(0, IDI_WINLOGO);
    wcex.hIconSm = LoadIcon(0, IDI_WINLOGO);
    wcex.hCursor = LoadCursor(0, IDC_ARROW);
    wcex.hInstance = 0;
    wcex.lpfnWndProc = msgHandlerMain;
    wcex.lpszClassName = "basic_draw";
    wcex.lpszMenuName = NULL;

    RegisterClassEx(&wcex);

    ret->idle_func = 0;
    return GET_INTERFACE(ret);
}