
include_directories(../../../include)

add_executable(vector_init vector_init.c)

target_link_libraries(vector_init basedefine test_framework)

set_property(TARGET vector_init PROPERTY FOLDER test/mathlib)