include_directories(../../../external/glew-1.9.0/include)
include_directories(../../../include)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
AUX_SOURCE_DIRECTORY(. BASICDRAW_SRC)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows")
add_executable(basic_draw ${BASICDRAW_SRC})
target_link_libraries(basic_draw mathlib memory glew opengl32)

set_property(TARGET basic_draw PROPERTY FOLDER test/opengl)