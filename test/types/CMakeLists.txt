
include_directories(../../include)

add_executable(test_type_uint8 uint8.c)
target_link_libraries(test_type_uint8 test_framework)
add_test(NAME test_type_uint8 COMMAND test_type_uint8)