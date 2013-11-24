include_directories(../../../include)
include_directories(../../../include/render_sys)

FILE(GLOB RENDERSYSINTERFACE_H . "*.h")
FILE(GLOB RENDERSYSINTERFACE_SRC . "*.c")
add_library(render_sys_interface ${RENDERSYSINTERFACE_SRC} ${RENDERSYSINTERFACE_H})
set_property(TARGET render_sys_interface PROPERTY FOLDER src/render_sys)
