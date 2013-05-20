#include "script/script.h"
#include "lua.h"
#include "interface_c.h"
int tolua_interface_open (lua_State*);

int main (void)
{
    struct sge_script_obj* script = sge_create_lua_script();
    int ret = sge_exec_buffer(script, "print(\"test\")");

    tolua_interface_open((lua_State*)sge_get_native_interface(script));
    ret = sge_exec_file(script, "test.lua");

//     lua_getglobal(L, "testmethod");
//     ret = lua_pcall(L,0,0,0);
// 
//     if(ret)
//     {
//         handleluaerror(L);
//     }
    sge_destory_script(script);
    return 0;
}
