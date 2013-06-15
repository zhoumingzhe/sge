include_directories(../../../external/glew-1.9.0/include)
include_directories(../../../include)
add_executable(basic_draw basic_draw.c)
target_link_libraries(basic_draw mathlib memory glew opengl32)

set_property(TARGET basic_draw PROPERTY FOLDER test/opengl)