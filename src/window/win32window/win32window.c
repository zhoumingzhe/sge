#include <windows.h>
#include "basedefine/runtime_assert.h"
#include "basedefine/utility.h"
#include "window_internal.h"
#include "memory/sge_memory.h"

struct sge_window_sys_win32
{
    struct sge_window_sys window_sys;
    on_idle idle_func;
};

struct sge_window_obj_win32
{
    struct sge_window_obj obj;
    HWND hwnd;
    on_resize resize_func;
};


void win32_show(struct sge_window_obj* obj, sge_int32 left, sge_int32 top,
                sge_int32 width, sge_int32 height)
{
    struct sge_window_obj_win32* win32_obj = get_container(obj, struct sge_window_obj_win32, obj);
    sge_runtime_assert(!win32_obj->hwnd);

    if(MessageBox(NULL, "Would you like to run in fullscreen?", "Fullscreen", MB_ICONQUESTION | MB_YESNO) == IDYES)
    {
        DEVMODE dmSettings = {0};
        EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmSettings); // Get current display settings

        win32_obj->hwnd = CreateWindowEx(0, "basic_draw", "basic_draw", WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // This is the commonly used style for fullscreen
            0, 0, dmSettings.dmPelsWidth, dmSettings.dmPelsHeight, NULL,
            NULL, 0, win32_obj);
    }
    else
    {
        win32_obj->hwnd = CreateWindowEx(0, "basic_draw", "basic_draw", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
            0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
            NULL, 0, win32_obj);
    }
    ShowWindow(win32_obj->hwnd, SW_SHOW);

    UpdateWindow(win32_obj->hwnd);
}
void win32_obj_destroy(struct sge_window_obj* obj)
{
    struct sge_window_obj_win32* win32_obj = get_container(obj, struct sge_window_obj_win32, obj);

    sge_runtime_assert(!!win32_obj->hwnd);
    DestroyWindow(win32_obj->hwnd);
    sge_free(win32_obj);
}
void win32_set_handler_resize(struct sge_window_obj* obj, on_resize func)
{
    struct sge_window_obj_win32* win32_obj = get_container(obj, struct sge_window_obj_win32, obj);
    win32_obj->resize_func = func;
}

static const struct sge_window_obj_table win32_window_obj_vptr =
{
    win32_show,
    win32_obj_destroy,
    win32_set_handler_resize
};

static struct sge_window_obj* win32_create_window(struct sge_window_sys* window_sys)
{
    struct sge_window_obj_win32* ret = (struct sge_window_obj_win32*)sge_malloc(sizeof(struct sge_window_obj_win32));
    ret->obj.vptr = &win32_window_obj_vptr;
    ret->hwnd = 0;
    ret->resize_func = 0;
    return &ret->obj;
}

static void win32_loop(struct sge_window_sys* window_sys)
{
    struct sge_window_sys_win32* win32_obj = get_container(window_sys, struct sge_window_sys_win32, window_sys);
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
    struct sge_window_sys_win32* ret = get_container(window_sys, struct sge_window_sys_win32, window_sys);
    UnregisterClass("basic_draw", 0);
    sge_free(ret);
}

static void win32_set_on_idle(struct sge_window_sys* window_sys, on_idle func)
{
    struct sge_window_sys_win32* ret = get_container(window_sys, struct sge_window_sys_win32, window_sys);
    ret->idle_func = func;
}

static const struct sge_window_sys_table win32_window_sys_vptr =
{
    win32_create_window,
    win32_loop,
    win32_destory,
    win32_set_on_idle
};

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
            obj_win32->resize_func(&obj_win32->obj, LOWORD(lParam), HIWORD(lParam));
        break;

    default:
        return DefWindowProc(hWnd, uiMsg, wParam, lParam);
    }
    return 0;
}

struct sge_window_sys* sge_window_sys_create_win32()
{
    struct sge_window_sys_win32* ret = 0;
    WNDCLASSEX wcex;

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

    ret = (struct sge_window_sys_win32*)sge_malloc(sizeof(struct sge_window_sys_win32));
    ret->window_sys.vptr = &win32_window_sys_vptr;
    ret->idle_func = 0;
    return &ret->window_sys;

}