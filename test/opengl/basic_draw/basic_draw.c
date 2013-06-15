#define GLEW_STATIC
#include <GL/glew.h>
#include <gl/wglew.h>

#include "mathlib/matrix.h"
#include "memory/sge_memory.h"

#include <stdio.h>
typedef struct {
    GLenum       type;
    const char*  filename;
    GLuint       shader;
} ShaderInfo;

HWND         g_hWnd;
HGLRC        g_hRC;
HDC          g_hDC;
HINSTANCE    g_hInstance;
WNDCLASS     g_windClass; 
RECT         g_windowRect;
sge_bool         g_ContinueRendering = 0;

int nStep = 0;
static GLchar*
    ReadShader( const char* filename )
{
    FILE* infile;
    int len;
    GLchar* source;


    fopen_s( &infile, filename, "rb" );

    if ( !infile ) {
        printf("Unable to open file '%s'\n", filename);
        return NULL;
    }

    fseek( infile, 0, SEEK_END );
    len = ftell( infile );
    fseek( infile, 0, SEEK_SET );

    source = (GLchar*)sge_malloc(len+1);

    fread( source, 1, len, infile );
    fclose( infile );

    source[len] = 0;

    return source;
}

GLuint
    LoadShaders( ShaderInfo* shaders )
{
    GLuint program;
    ShaderInfo* entry = shaders;
    GLint linked;


    if ( shaders == NULL ) { return 0; }

    program = glCreateProgram();

    while ( entry->type != GL_NONE ) {
        GLchar* source = ReadShader( entry->filename );
        GLuint shader = glCreateShader( entry->type );
        const GLchar* src = source;
        GLint compiled;

        entry->shader = shader;

        if ( source == NULL ) {
            for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
                glDeleteShader( entry->shader );
                entry->shader = 0;
            }

            return 0;
        }
        glShaderSource( shader, 1, &src, NULL );
        sge_free(source);

        glCompileShader( shader );

        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
        if ( !compiled ) {
            GLsizei len;
            GLchar* log;

            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

            log = (GLchar*)sge_malloc(len+1);
            glGetShaderInfoLog( shader, len, &len, log );
            printf("Shader compilation failed: %s\n", log);;
            sge_free(log);

            return 0;
        }

        glAttachShader( program, shader );

        ++entry;
    }

    glLinkProgram( program );

    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
        GLsizei len;
        GLchar* log;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

        log = (GLchar*)sge_malloc(len+1);
        glGetProgramInfoLog( program, len, &len, log );
        printf("Shader linking failed: %s\n");
        sge_free(log);

        for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
            glDeleteShader( entry->shader );
            entry->shader = 0;
        }

        return 0;
    }

    return program;
}


float aspect;
GLuint render_prog;
GLuint vao;
GLuint vbo;
GLuint ebo;

GLint render_model_matrix_loc;
GLint render_projection_matrix_loc;

void Display(void)
{


    sge_mat44f model_matrix;
    sge_mat44f projection_matrix = sge_mat44f_perspective_rh_gl(2.0f, 2*aspect, 1.0f, 500.0f);

    if(!g_ContinueRendering)
        return;

    // Setup
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activate simple shading program
    glUseProgram(render_prog);

    // Set up the model and projection matrix
    glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, &projection_matrix.m[0][0]);

    // Set up for a glDrawElements call
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // Draw Arrays...
    model_matrix = sge_mat44f_translate(-3.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, &model_matrix.m[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // DrawElements
    model_matrix = sge_mat44f_translate(-1.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, &model_matrix.m[0][0]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

    // DrawElementsBaseVertex
    model_matrix = sge_mat44f_translate(1.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, &model_matrix.m[0][0]);
    glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 1);

    // DrawArraysInstanced
    model_matrix = sge_mat44f_translate(3.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, &model_matrix.m[0][0]);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);

    SwapBuffers(g_hDC);
}

void Reshape(int width, int height)
{
    glViewport(0, 0 , width, height);
    aspect = (float)(height) / (float)(width);
}

void APIENTRY DebugOutputCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    GLvoid* userParam)
{
    OutputDebugStringA(message);
    OutputDebugStringA("\n");
}

void Finalize(void)
{
    glUseProgram(0);
    glDeleteProgram(render_prog);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
static ShaderInfo shader_info[] =
{
    { GL_VERTEX_SHADER, "primitive_restart.vs.glsl" },
    { GL_FRAGMENT_SHADER, "primitive_restart.fs.glsl" },
    { GL_NONE, NULL }
};
// A single triangle
static const GLfloat vertex_positions[] =
{
    -1.0f, -1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  0.0f, 1.0f,
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 1.0f,
};

// Color for each vertex
static const GLfloat vertex_colors[] =
{
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f
};

// Indices for the triangle strips
static const GLushort vertex_indices[] =
{
    0, 1, 2
};

///////////////////////////////////////////////////////////////////////////////
// Callback functions to handle all window functions this app cares about.
// Once complete, pass message on to next app in the hook chain.
LRESULT CALLBACK WndProc(	HWND	hWnd,		// Handle For This Window
                         UINT	uMsg,		// Message For This Window
                         WPARAM	wParam,		// Additional Message Information
                         LPARAM	lParam)		// Additional Message Information
{
    unsigned int key = 0;

    // Handle relevant messages individually
    switch(uMsg)
    {
    case WM_ACTIVATE:
    case WM_SETFOCUS:
        Display();
        return 0;
    case WM_SIZE:
        Reshape(LOWORD(lParam),HIWORD(lParam));
        Display();
        break;
    case WM_CLOSE:
        g_ContinueRendering = 0;
        PostQuitMessage(0);
        return 0;
    case WM_KEYDOWN:
        key = (unsigned int)wParam;
        if(key == 32)
        {
            nStep++;
            if(nStep > 5)
                nStep = 0;
        }
        return 0;
    default:
        // Nothing to do now
        break;
    }

    // Pass All Unhandled Messages To DefWindowProc
    return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

///////////////////////////////////////////////////////////////////////////////
// Setup the actual window and related state.
// Create the window, find a pixel format, create the OpenGL context
sge_bool SetupWindow(int nWidth, int nHeight)
{
    sge_bool bRetVal = 1;

    int nPixCount = 0;
    int nWindowWidth;
    int nWindowHeight;
    GLenum err;
    int nWindowX = 0;
    int nWindowY = 0;
    int nPixelFormat  = -1;
    PIXELFORMATDESCRIPTOR pfd;

    DWORD dwExtStyle;
    DWORD dwWindStyle;

    HINSTANCE g_hInstance = GetModuleHandle(NULL);

    TCHAR szWindowName[50] =  TEXT("Block Redux");
    TCHAR szClassName[50]  =  TEXT("OGL_CLASS");

    // Specify the important attributes we care about
    int pixAttribs[] = { WGL_SUPPORT_OPENGL_ARB, 1, // Must support OGL rendering
        WGL_DRAW_TO_WINDOW_ARB, 1, // pf that can run a window
        WGL_ACCELERATION_ARB,   1, // must be HW accelerated
        WGL_RED_BITS_ARB,       8, // 8 bits of red precision in window
        WGL_GREEN_BITS_ARB,     8, // 8 bits of green precision in window
        WGL_BLUE_BITS_ARB,      8, // 8 bits of blue precision in window
        WGL_DEPTH_BITS_ARB,     16, // 16 bits of depth precision for window
        WGL_PIXEL_TYPE_ARB,      WGL_TYPE_RGBA_ARB, // pf should be RGBA type
        0}; // NULL termination

    // setup window class
    g_windClass.lpszClassName = szClassName;                // Set the name of the Class
    g_windClass.lpfnWndProc   = (WNDPROC)WndProc;
    g_windClass.hInstance     = g_hInstance;                // Use this module for the module handle
    g_windClass.hCursor       = LoadCursor(NULL, IDC_ARROW);// Pick the default mouse cursor
    g_windClass.hIcon         = LoadIcon(NULL, IDI_WINLOGO);// Pick the default windows icons
    g_windClass.hbrBackground = NULL;                       // No Background
    g_windClass.lpszMenuName  = NULL;                       // No menu for this window
    g_windClass.style         = CS_HREDRAW | CS_OWNDC |     // set styles for this class, specifically to catch
        CS_VREDRAW;                 // window redraws, unique DC, and resize
    g_windClass.cbClsExtra    = 0;                          // Extra class memory
    g_windClass.cbWndExtra    = 0;                          // Extra window memory

    // Register the newly defined class
    if(!RegisterClass( &g_windClass ))
        bRetVal = 0;

    dwExtStyle  = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    dwWindStyle = WS_OVERLAPPEDWINDOW;
    ShowCursor(TRUE);

    g_windowRect.left   = nWindowX;
    g_windowRect.right  = nWindowX + nWidth;
    g_windowRect.top    = nWindowY;
    g_windowRect.bottom = nWindowY + nHeight;

    // Setup window width and height
    AdjustWindowRectEx(&g_windowRect, dwWindStyle, FALSE, dwExtStyle);

    //Adjust for adornments
    nWindowWidth = g_windowRect.right   - g_windowRect.left;
    nWindowHeight = g_windowRect.bottom - g_windowRect.top;

    // Create window
    g_hWnd = CreateWindowEx(dwExtStyle,     // Extended style
        szClassName,    // class name
        szWindowName,   // window name
        dwWindStyle |        
        WS_CLIPSIBLINGS | 
        WS_CLIPCHILDREN,// window stlye
        nWindowX,       // window position, x
        nWindowY,       // window position, y
        nWindowWidth,   // height
        nWindowHeight,  // width
        NULL,           // Parent window
        NULL,           // menu
        g_hInstance,    // instance
        NULL);          // pass this to WM_CREATE

    // now that we have a window, setup the pixel format descriptor
    g_hDC = GetDC(g_hWnd);

    // Set a dummy pixel format so that we can get access to wgl functions
    SetPixelFormat( g_hDC, 1,&pfd);
    // Create OGL context and make it current
    g_hRC = wglCreateContext( g_hDC );
    wglMakeCurrent( g_hDC, g_hRC );

    if (g_hDC == 0 ||
        g_hDC == 0)
    {
        bRetVal = 0;
        printf("!!! An error occured creating an OpenGL window.\n");
    }

    // Setup GLEW which loads OGL function pointers
    glewExperimental=1;
    err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        bRetVal = 0;
        printf("Error: %s\n", glewGetErrorString(err));
    }

    if (glDebugMessageCallbackARB != NULL)
        glDebugMessageCallbackARB(DebugOutputCallback, 0);

    printf("This system supports OpenGL Version %s.\n", glGetString(GL_VERSION));

    // Now that extensions are setup, delete window and start over picking a real format.
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(g_hRC);
    ReleaseDC(g_hWnd, g_hDC);
    DestroyWindow(g_hWnd);

    // Create the window again
    g_hWnd = CreateWindowEx(dwExtStyle,     // Extended style
        szClassName,    // class name
        szWindowName,   // window name
        dwWindStyle |        
        WS_CLIPSIBLINGS | 
        WS_CLIPCHILDREN,// window stlye
        nWindowX,       // window position, x
        nWindowY,       // window position, y
        nWindowWidth,   // height
        nWindowHeight,  // width
        NULL,           // Parent window
        NULL,           // menu
        g_hInstance,    // instance
        NULL);          // pass this to WM_CREATE

    g_hDC = GetDC(g_hWnd);

    // Ask OpenGL to find the most relevant format matching our attribs
    // Only get one format back.
    wglChoosePixelFormatARB(g_hDC, &pixAttribs[0], NULL, 1, &nPixelFormat, (UINT*)&nPixCount);

    if(nPixelFormat == -1) 
    {
        // Couldn't find a format, perhaps no 3D HW or drivers are installed
        g_hDC = 0;
        g_hDC = 0;
        bRetVal = 0;
        printf("!!! An error occurred trying to find a pixel format with the requested attribs.\n");
    }
    else
    {
        GLint attribs[] = {WGL_CONTEXT_MAJOR_VERSION_ARB,  3,
            WGL_CONTEXT_MINOR_VERSION_ARB,  3,
            0 };

        // Got a format, now set it as the current one
        SetPixelFormat( g_hDC, nPixelFormat, &pfd );


        g_hRC = wglCreateContextAttribsARB(g_hDC, 0, attribs);
        if (g_hRC == NULL)
        {
            printf("!!! Could not create an OpenGL 3.3 context.\n");
            attribs[3] = 2;
            g_hRC = wglCreateContextAttribsARB(g_hDC, 0, attribs);
            if (g_hRC == NULL)
            {
                printf("!!! Could not create an OpenGL 3.2 context.\n");
                attribs[3] = 1;
                g_hRC = wglCreateContextAttribsARB(g_hDC, 0, attribs);
                if (g_hRC == NULL)
                {
                    printf("!!! Could not create an OpenGL 3.1 context.\n");
                    attribs[3] = 0;
                    g_hRC = wglCreateContextAttribsARB(g_hDC, 0, attribs);
                    if (g_hRC == NULL)
                    {
                        printf("!!! Could not create an OpenGL 3.0 context.\n");
                        printf("!!! OpenGL 3.0 and higher are not supported on this system.\n");
                    }
                }
            }
        }

        wglMakeCurrent( g_hDC, g_hRC );
    }

    if (g_hDC == 0 ||
        g_hDC == 0)
    {
        bRetVal = 0;
        printf("!!! An error occured creating an OpenGL window.\n");
    }

    // If everything went as planned, display the window 
    if( bRetVal )
    {
        ShowWindow( g_hWnd, SW_SHOW );
        SetForegroundWindow( g_hWnd );
        SetFocus( g_hWnd );
        g_ContinueRendering = 1;
    }

    return bRetVal;
}

///////////////////////////////////////////////////////////////////////////////
// Cleanup window, OGL context and related state
// Called on exit and on error
sge_bool KillWindow( )
{ 
    sge_bool bRetVal = 1;
    TCHAR szClassName[50]  =  TEXT("OGL_CLASS");

    //Cleanup OGL RC
    if(g_hRC) 
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(g_hRC);
        g_hRC = NULL;
    }

    // release the DC
    if(g_hDC)
    {
        ReleaseDC(g_hWnd, g_hDC);
        g_hDC = NULL;
    }

    // Destroy the window
    if(g_hWnd)
    {
        DestroyWindow(g_hWnd);
        g_hWnd = NULL;;
    }

    // Delete the window class
    UnregisterClass(szClassName, g_hInstance);
    g_hInstance = NULL;
    ShowCursor(TRUE);
    return bRetVal;
}
void mainLoop()
{
    MSG msg;

    // Check for waiting mssgs
    if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
    {
        if (msg.message==WM_QUIT)
        {
            g_ContinueRendering = 0;
        }
        else
        {
            // Deal with mssgs
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    else
    {
        Display();
    }
}
int main(int argc, char ** argv)
{
    SetupWindow(800, 600);

    render_prog = LoadShaders(shader_info);

    glUseProgram(render_prog);

    // "model_matrix" is actually an array of 4 matrices
    render_model_matrix_loc = glGetUniformLocation(render_prog, "model_matrix");
    render_projection_matrix_loc = glGetUniformLocation(render_prog, "projection_matrix");

    // Set up the element array buffer
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

    // Set up the vertex attributes
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions) + sizeof(vertex_colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vertex_positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(vertex_positions));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (g_ContinueRendering)
    {   
        mainLoop();
        Sleep(0);
    }
    Finalize();

    return 0;
}
