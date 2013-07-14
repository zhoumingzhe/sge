include_directories(../../../external/glew-1.9.0/include)
include_directories(../../../include)
include_directories(../../../include/render_sys)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
AUX_SOURCE_DIRECTORY(. BASICDRAW_SRC)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows")
add_executable(basic_draw ${BASICDRAW_SRC})
target_link_libraries(basic_draw basedefine mathlib windowbase win32window
 memory glew opengl32 render_sys_interface render_sys_opengl)

set_property(TARGET basic_draw PROPERTY FOLDER test/opengl)