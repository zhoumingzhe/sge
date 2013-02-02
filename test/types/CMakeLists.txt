
include_directories(../../include)

<<<<<<< HEAD
add_executable(test_type_uint8 uint8.c)
target_link_libraries(test_type_uint8 test_framework)
add_test(NAME test_type_uint8 COMMAND test_type_uint8)
=======
add_executable(test_types types.c)
target_link_libraries(test_types test_framework)
add_test(NAME test_types COMMAND test_types)
>>>>>>> types and test frameworks
