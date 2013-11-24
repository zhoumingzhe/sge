include_directories(../render_sys_interface)
include_directories(../../../include)
include_directories(../../../include/render_sys)
include_directories(../../../external/glew-1.9.0/include)
FILE(GLOB OPENGL_H . "*.h")
FILE(GLOB OPENGL_SRC . "*.c")

#shared library
#add_library(render_sys_opengl SHARED ${OPENGL_SRC} ${OPENGL_H} win32_support/win32_support.c)
#static library
add_library(render_sys_opengl ${OPENGL_SRC} ${OPENGL_H} win32_support/win32_support.c)
set_property(TARGET render_sys_opengl PROPERTY FOLDER src/render_sys)
target_link_libraries(render_sys_opengl opengl32 glew memory windowbase)
