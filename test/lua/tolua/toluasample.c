#include "script/script.h"
#include "lua.h"
#include "interface_c.h"
int tolua_interface_open (lua_State*);

void run_all_test()
{
    struct sge_script_obj* script = sge_create_lua_script();
    int ret = sge_exec_buffer(script, "print(\"test\")");

    tolua_interface_open((lua_State*)sge_get_native_interface(script));
    ret = sge_exec_file(script, "test.lua");
    ret = sge_call_func(script, "testmethod");
    sge_destory_script(script);
}
