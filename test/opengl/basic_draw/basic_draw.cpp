#define GLEW_STATIC
#include <GL/glew.h>
#define FREEGLUT_STATIC
#include <GL/freeglut.h>
extern "C"
{
#include "mathlib/matrix.h"
};
#include <cstdlib>
#include <iostream>
typedef struct {
    GLenum       type;
    const char*  filename;
    GLuint       shader;
} ShaderInfo;

static const GLchar*
    ReadShader( const char* filename )
{
    FILE* infile;
    fopen_s( &infile, filename, "rb" );

    if ( !infile ) {
        std::cerr << "Unable to open file '" << filename << "'" << std::endl;
        return NULL;
    }

    fseek( infile, 0, SEEK_END );
    int len = ftell( infile );
    fseek( infile, 0, SEEK_SET );

    GLchar* source = new GLchar[len+1];

    fread( source, 1, len, infile );
    fclose( infile );

    source[len] = 0;

    return const_cast<const GLchar*>(source);
}

GLuint
    LoadShaders( ShaderInfo* shaders )
{
    if ( shaders == NULL ) { return 0; }

    GLuint program = glCreateProgram();

    ShaderInfo* entry = shaders;
    while ( entry->type != GL_NONE ) {
        GLuint shader = glCreateShader( entry->type );

        entry->shader = shader;

        const GLchar* source = ReadShader( entry->filename );
        if ( source == NULL ) {
            for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
                glDeleteShader( entry->shader );
                entry->shader = 0;
            }

            return 0;
        }

        glShaderSource( shader, 1, &source, NULL );
        delete [] source;

        glCompileShader( shader );

        GLint compiled;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
        if ( !compiled ) {
            GLsizei len;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

            GLchar* log = new GLchar[len+1];
            glGetShaderInfoLog( shader, len, &len, log );
            std::cerr << "Shader compilation failed: " << log << std::endl;
            delete [] log;

            return 0;
        }

        glAttachShader( program, shader );

        ++entry;
    }

    glLinkProgram( program );

    GLint linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
        GLsizei len;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

        GLchar* log = new GLchar[len+1];
        glGetProgramInfoLog( program, len, &len, log );
        std::cerr << "Shader linking failed: " << log << std::endl;
        delete [] log;

        for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
            glDeleteShader( entry->shader );
            entry->shader = 0;
        }

        return 0;
    }

    return program;
}

class VermillionApplication
{
protected:
    inline VermillionApplication(void) {}
    virtual ~VermillionApplication(void) {}

    static VermillionApplication * s_app;

    static void DisplayFunc(void);
    static void ReshapeFunc(int width, int height);

    static void APIENTRY DebugOutputCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        GLvoid* userParam);

public:
    static void MainLoop(void);

    virtual void Initialize(const char * title = 0)
    {
        int one = 1;
        char * name = "name";

        glutInitContextFlags(GLUT_DEBUG);
        // glutInitContextProfile(GLUT_CORE_PROFILE);
        // glutInitContextVersion(4, 3);

        glutInitWindowSize(1024, 768);
        glutInitWindowPosition (140, 140);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInit(&one, &name);

        glutCreateWindow( title ? title : "OpenGL Application" );
        glutDisplayFunc(DisplayFunc);
        glutReshapeFunc(ReshapeFunc);

        glewInit();

        if (glDebugMessageCallbackARB != NULL)
            glDebugMessageCallbackARB(DebugOutputCallback, this);
    }

    virtual void Display(bool auto_redraw = true)
    {
        glutSwapBuffers();
        if (auto_redraw)
        {
            glutPostRedisplay();
        }
    }

    virtual void Finalize(void)
    {

    }

    virtual void Reshape(int width, int height)
    {
        glViewport(0, 0, width, height);
    }
};

void vglAttachShaderSource(GLuint prog, GLenum type, const char * source)
{
    GLuint sh;

    sh = glCreateShader(type);
    glShaderSource(sh, 1, &source, NULL);
    glCompileShader(sh);
    char buffer[4096];
    glGetShaderInfoLog(sh, sizeof(buffer), NULL, buffer);
    glAttachShader(prog, sh);
    glDeleteShader(sh);
}


#define _USE_MATH_DEFINES  1 // Include constants defined in math.h
#include <math.h>

class DrawCommandExample : public VermillionApplication
{
public:
    typedef class VermillionApplication base;
    static VermillionApplication * Create(void)
    {
        return (s_app = new DrawCommandExample);
    }
    // Override functions from base class
    virtual void Initialize(const char * title);
    virtual void Display(bool auto_redraw);
    virtual void Finalize(void);
    virtual void Reshape(int width, int height);

    // Member variables
    float aspect;
    GLuint render_prog;
    GLuint vao[1];
    GLuint vbo[1];
    GLuint ebo[1];

    GLint render_model_matrix_loc;
    GLint render_projection_matrix_loc;
};

VermillionApplication * VermillionApplication::s_app;

void VermillionApplication::DisplayFunc(void)
{
    s_app->Display();
}

void VermillionApplication::ReshapeFunc(int width,int height)
{
    s_app->Reshape(width, height);
}

void VermillionApplication::MainLoop(void)
{
    for (;;)
        glutMainLoopEvent();
}

int main(int argc, char ** argv)
{
    VermillionApplication * app = DrawCommandExample::Create();

    app->Initialize("Drawing Commands Example");
    app->MainLoop();
    app->Finalize();

    return 0;
}
void APIENTRY VermillionApplication::DebugOutputCallback(
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

void DrawCommandExample::Initialize(const char * title)
{
    base::Initialize(title);

    static ShaderInfo shader_info[] =
    {
        { GL_VERTEX_SHADER, "primitive_restart.vs.glsl" },
        { GL_FRAGMENT_SHADER, "primitive_restart.fs.glsl" },
        { GL_NONE, NULL }
    };

    render_prog = LoadShaders(shader_info);

    glUseProgram(render_prog);

    // "model_matrix" is actually an array of 4 matrices
    render_model_matrix_loc = glGetUniformLocation(render_prog, "model_matrix");
    render_projection_matrix_loc = glGetUniformLocation(render_prog, "projection_matrix");

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

    // Set up the element array buffer
    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

    // Set up the vertex attributes
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions) + sizeof(vertex_colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vertex_positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(vertex_positions));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void DrawCommandExample::Display(bool auto_redraw)
{
    sge_mat44f model_matrix;

    // Setup
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activate simple shading program
    glUseProgram(render_prog);

    // Set up the model and projection matrix
    sge_mat44f projection_matrix = sge_mat44f_perspective_rh_gl(2.0f, 2*aspect, 1.0f, 500.0f);
    glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, &projection_matrix.m[0][0]);

    // Set up for a glDrawElements call
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);

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

    base::Display();
}

void DrawCommandExample::Finalize(void)
{
    glUseProgram(0);
    glDeleteProgram(render_prog);
    glDeleteVertexArrays(1, vao);
    glDeleteBuffers(1, vbo);
}

void DrawCommandExample::Reshape(int width, int height)
{
    glViewport(0, 0 , width, height);

    aspect = float(height) / float(width);
}
