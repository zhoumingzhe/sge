#include "../render_headers_opengl.h"
#include <windows.h>
#include <GL/wglew.h>
#include "basedefine/types.h"
#include "basedefine/utility.h"
#include "memory/sge_memory.h"
#include "window/window.h"
#include "../platform_support.h"
#include "../render_context_opengl.h"
LRESULT CALLBACK msgHandlerSimpleOpenGLClass(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    switch(uiMsg)
    {
    case WM_PAINT:									
        BeginPaint(hWnd, &ps);							
        EndPaint(hWnd, &ps);					
        break;

    default:
        return DefWindowProc(hWnd, uiMsg, wParam, lParam); // Default window procedure
    }
    return 0;
}

sge_bool init_glew()
{
    WNDCLASSEX wc;
    HWND hWndFake = 0;
    HDC hDc = 0;
    PIXELFORMATDESCRIPTOR pfd;
    int iPixelFormat = 0;
    HGLRC hRCFake = 0;

    wc.cbSize = sizeof(wc);
    wc.style =  CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
    wc.lpfnWndProc = (WNDPROC) msgHandlerSimpleOpenGLClass;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = 0;
    wc.hIcon = LoadIcon(0, IDI_WINLOGO);
    wc.hIconSm = LoadIcon(0, IDI_WINLOGO);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = "glewinit";

    if(!RegisterClassEx(&wc))
        return 0;

    hWndFake = CreateWindow("glewinit", "FAKE",
        WS_OVERLAPPEDWINDOW | WS_MAXIMIZE | WS_CLIPCHILDREN,
        0, 0, CW_USEDEFAULT, CW_USEDEFAULT, 0,
        0, 0, 0);

    if(!hWndFake)
        return 0;

    hDc = GetDC(hWndFake);

    // First, choose false pixel format

    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion   = 1;
    pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iPixelFormat = ChoosePixelFormat(hDc, &pfd);
    if (iPixelFormat == 0)
        return 0;

    if(!SetPixelFormat(hDc, iPixelFormat, &pfd))
        return 0;

    // Create the false, old style context (OpenGL 2.1 and before)

    hRCFake = wglCreateContext(hDc);
    wglMakeCurrent(hDc, hRCFake);

    glewInit();

    wglMakeCurrent(0, 0);
    wglDeleteContext(hRCFake);
    ReleaseDC(hWndFake, hDc);
    DestroyWindow(hWndFake);

    return 1;
}
BEGIN_IMPLEMENTATION(sge_render_context_opengl_win32, sge_render_context_opengl)
    HWND hwnd;
    HDC hdc;
    HGLRC hrc;
END_IMPLEMENTATION

static void opengl_context_present(struct sge_render_context* context)
{
    VIRTUAL_CONTAINER(context_opengl, context, struct sge_render_context_opengl);

    VIRTUAL_CONTAINER(context_opengl_win32, context_opengl, struct sge_render_context_opengl_win32);

    SwapBuffers(context_opengl_win32->hdc);
}

static void opengl_context_destroy(struct sge_render_context* context)
{
    VIRTUAL_CONTAINER(context_opengl, context, struct sge_render_context_opengl);

    VIRTUAL_CONTAINER(context_opengl_win32, context_opengl, struct sge_render_context_opengl_win32);

    wglMakeCurrent(0, 0);
    wglDeleteContext(context_opengl_win32->hrc);
    ReleaseDC(context_opengl_win32->hwnd, context_opengl_win32->hdc);
    sge_free(context_opengl);
}
BEGIN_VTABLE_INSTANCE(sge_render_context_opengl_win32, sge_render_context)
    opengl_context_present,
    opengl_context_destroy,
    opengl_context_clear,
    opengl_create_vertex_buffer,
END_VTABLE_INSTANCE

struct sge_render_context* create_context(struct sge_render_sys* render_sys, struct sge_window_obj* window_obj)
{
    HWND hwnd = (HWND)sge_window_get_native_obj(window_obj);
    HDC hDC = GetDC(hwnd);
    HGLRC hRC;
    PIXELFORMATDESCRIPTOR pfd;

    if(WGLEW_ARB_create_context && WGLEW_ARB_pixel_format)
    {
        const int iPixelFormatAttribList[] =
        {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
            WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
            WGL_COLOR_BITS_ARB, 32,
            WGL_DEPTH_BITS_ARB, 24,
            WGL_STENCIL_BITS_ARB, 8,
            0 // End of attributes list
        };
        int iContextAttribs[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            0 // End of attributes list
        };

        int iPixelFormat, iNumFormats;
        wglChoosePixelFormatARB(hDC, iPixelFormatAttribList, NULL, 1, &iPixelFormat, (UINT*)&iNumFormats);

        if(!SetPixelFormat(hDC, iPixelFormat, &pfd))return 0;

        hRC = wglCreateContextAttribsARB(hDC, 0, iContextAttribs);

        if(hRC)
        {
            CREATE_INSTANCE2(context, sge_render_context_opengl_win32, sge_malloc);
            init_opengl_context(GET_INTERFACE(context));
            context->hwnd = hwnd;
            context->hdc = hDC;
            context->hrc = hRC;
            wglMakeCurrent(hDC, hRC);

            return GET_INTERFACE2(context);
        }
        else
            return 0;
    }
    else
        return 0;
}