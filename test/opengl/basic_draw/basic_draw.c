#define GLEW_STATIC
#include <GL/glew.h>
#define FREEGLUT_STATIC
#include <GL/freeglut.h>

#include "mathlib/matrix.h"
#include "memory/sge_memory.h"

#include <stdio.h>
typedef struct {
    GLenum       type;
    const char*  filename;
    GLuint       shader;
} ShaderInfo;

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

    glutSwapBuffers();
    glutPostRedisplay();
}

void Reshape(int width, int height)
{
    glViewport(0, 0 , width, height);
    aspect = (float)(height) / (float)(width);
}

void MainLoop(void)
{
    for (;;)
        glutMainLoopEvent();
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

int main(int argc, char ** argv)
{

    int one = 1;
    char * name = "name";

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

    glutInitContextFlags(GLUT_DEBUG);
    // glutInitContextProfile(GLUT_CORE_PROFILE);
    // glutInitContextVersion(4, 3);

    glutInitWindowSize(1024, 768);
    glutInitWindowPosition (140, 140);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInit(&one, &name);

    glutCreateWindow("OpenGL Application");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);

    glewInit();

    if (glDebugMessageCallbackARB != NULL)
        glDebugMessageCallbackARB(DebugOutputCallback, 0);

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

    MainLoop();
    Finalize();

    return 0;
}
