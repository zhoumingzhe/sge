include_directories(../../../include)

set(mathlib_test_deps basedefine test_framework mathlib)

add_executable(vector_init vector_init.c)
target_link_libraries(vector_init ${mathlib_test_deps})
add_test(NAME vector_init COMMAND vector_init)
set_property(TARGET vector_init PROPERTY FOLDER test/mathlib)


add_executable(vector_floor vector_floor.c)
target_link_libraries(vector_floor ${mathlib_test_deps})
add_test(NAME vector_floor COMMAND vector_floor)
set_property(TARGET vector_floor PROPERTY FOLDER test/mathlib)


add_executable(vector_ceiling vector_ceiling.c)
target_link_libraries(vector_ceiling ${mathlib_test_deps})
add_test(NAME vector_ceiling COMMAND vector_ceiling)
set_property(TARGET vector_ceiling PROPERTY FOLDER test/mathlib)


add_executable(matrix_init matrix_init.c)
target_link_libraries(matrix_init ${mathlib_test_deps})
add_test(NAME matrix_init COMMAND matrix_init)
set_property(TARGET matrix_init PROPERTY FOLDER test/mathlib)

