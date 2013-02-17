#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "interface_c.h"
int tolua_interface_open (lua_State*);

void handleluaerror(lua_State*L)
{
    const char *msg = lua_tostring(L, -1);
    printf("%s", msg);
    lua_pop(L, 1);
}
void printtop(lua_State *L)
{
    int top = lua_gettop(L);
    printf("top: %d", top);
}
int main (void)
{
    int ret;
    lua_State* L = luaL_newstate();
    printtop(L);
    luaL_openlibs(L);
    printtop(L);
    ret = luaL_dostring(L, "print(\"test\")");
    printtop(L);
    if(ret)
    {
        handleluaerror(L);
        printtop(L);
    }
    printtop(L);
    tolua_interface_open(L);
    printtop(L);
    ret = luaL_dofile(L,"test.lua");
    printtop(L);
    if(ret)
    {
        handleluaerror(L);
        printtop(L);
    }
    printtop(L);
    lua_close(L);
    return 0;
}
