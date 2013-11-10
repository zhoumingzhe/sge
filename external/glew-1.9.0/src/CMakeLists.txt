include_directories(../include)
add_definitions(-DGLEW_STATIC)
add_library(glew glew.c)

set_property(TARGET glew PROPERTY FOLDER external/opengl)

add_executable(glewinfo glewinfo.c)
add_executable(visualinfo visualinfo.c)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
set_property(TARGET glewinfo PROPERTY FOLDER external/opengl)
set_property(TARGET visualinfo PROPERTY FOLDER external/opengl)

target_link_libraries(glewinfo opengl32 glew)

target_link_libraries(visualinfo opengl32 glu32 glew)