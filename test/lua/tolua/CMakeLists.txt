include_directories(
.
../../../external/lua-5.2.0/src
../../../external/tolua-5.2.0/include
../../../include
)

ADD_CUSTOM_COMMAND(
   OUTPUT interface.c
   COMMAND tolua -n interface -o interface.c ${CMAKE_CURRENT_SOURCE_DIR}/interface.pkg
   DEPENDS tolua ${CMAKE_CURRENT_SOURCE_DIR}/interface.pkg
   )


add_executable(tolua_test toluasample.c interface.c interface_c.c)
target_link_libraries(tolua_test tolualib luascript scriptbase lua memory basedefine test_framework)
add_test(NAME tolua_test COMMAND tolua_test)
set_property(TARGET tolua_test PROPERTY FOLDER test/lua)
