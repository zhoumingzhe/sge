#include "common_header.h"

#include "win_OpenGLApp.h"


COpenGLControl oglControl; // OpenGL Control

LRESULT CALLBACK msgHandlerMain(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uiMsg)
	{

		case WM_CLOSE:
			PostQuitMessage(0);
			break;

		case WM_SIZE:
			oglControl.resizeOpenGLViewportFull();
			oglControl.setProjection3D(0.002f*float(LOWORD(lParam))/float(HIWORD(lParam)), 0.002f, 0.001f, 1000.0f);
			break;

		default:
			return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int iShow)
{

    HWND hWnd; // Handle to application window
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

    if(MessageBox(NULL, "Would you like to run in fullscreen?", "Fullscreen", MB_ICONQUESTION | MB_YESNO) == IDYES)
    {
        DEVMODE dmSettings = {0};
        EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmSettings); // Get current display settings

        hWnd = CreateWindowEx(0, "basic_draw", "basic_draw", WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // This is the commonly used style for fullscreen
            0, 0, dmSettings.dmPelsWidth, dmSettings.dmPelsHeight, NULL,
            NULL, 0, NULL);
    }
    else hWnd = CreateWindowEx(0, "basic_draw", "basic_draw", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
        NULL, 0, NULL);

    if(!oglControl.initOpenGL(0, &hWnd, 3, 3, initScene, renderScene, releaseScene, &oglControl))
        return 0;

    ShowWindow(hWnd, SW_SHOW);

    // Just to send WM_SIZE message again
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
    UpdateWindow(hWnd);

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
            oglControl.render(&oglControl);
        }
    }

    oglControl.releaseOpenGLControl(&oglControl);

    DestroyWindow(hWnd);
    UnregisterClass("basic_draw", 0);
    COpenGLControl::unregisterSimpleOpenGLClass(0);

	return 0;
}

