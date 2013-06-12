include_directories(../../../external/glew-1.9.0/include)
include_directories(../../../external/freeglut-2.8.1/include)
include_directories(../../../include)
add_definitions(-DGLUT_DISABLE_ATEXIT_HACK -DFREEGLUT_LIB_PRAGMAS=0)
add_executable(basic_draw basic_draw.cpp)
target_link_libraries(basic_draw mathlib glew freeglut opengl32 winmm)

set_property(TARGET basic_draw PROPERTY FOLDER test/opengl)