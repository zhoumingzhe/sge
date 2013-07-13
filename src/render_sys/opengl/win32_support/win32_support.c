#include <windows.h>
#define GLEW_STATIC
#include "GL/glew.h"
#include "basedefine/types.h"

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
    DestroyWindow(hWndFake);

    return 1;
}