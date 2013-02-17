include_directories(../../../external/lua-5.2.0/src ../../../external/tolua-5.2.0/include .)

ADD_CUSTOM_COMMAND(
   OUTPUT interface.c
   COMMAND tolua -n interface -o ${CMAKE_CURRENT_BINARY_DIR}/interface.c ${CMAKE_CURRENT_SOURCE_DIR}/interface.pkg
   DEPENDS tolua ${CMAKE_CURRENT_SOURCE_DIR}/interface.pkg
   )


add_executable(toluasample toluasample.c interface.c interface_c.c)
target_link_libraries(toluasample lua tolualib)
#add_test(NAME test_types COMMAND test_types)
set_property(TARGET toluasample PROPERTY FOLDER test/lua)

