include_directories(../../../include)

add_executable(test_types types.c)
target_link_libraries(test_types basedefine test_framework)
add_test(NAME test_types COMMAND test_types)
set_property(TARGET test_types PROPERTY FOLDER test/types)

