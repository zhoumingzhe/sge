include_directories(../include)
add_definitions(-DGLEW_STATIC)
add_library(glew glew.c)

set_property(TARGET glew PROPERTY FOLDER external/opengl)