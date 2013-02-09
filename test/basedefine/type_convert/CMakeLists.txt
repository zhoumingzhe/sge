include_directories(../../../include)

add_executable(test_type_convert type_convert.c)
target_link_libraries(test_type_convert test_framework basedefine)
add_test(NAME test_type_convert COMMAND test_type_convert)

