include_directories(../../../external/lua-5.2.0/src ../../../external/tolua-5.2.0/include)

add_executable(toluasample toluasample.c interface.c interface_c.c)
target_link_libraries(toluasample lua tolualib)
#add_test(NAME test_types COMMAND test_types)
set_property(TARGET toluasample PROPERTY FOLDER test/lua)

