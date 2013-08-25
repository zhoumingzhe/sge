#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include "script_internal.h"
#include "memory/sge_memory.h"

BEGIN_IMPLEMENTATION(sge_lua_obj, sge_script_obj)
    lua_State *l;
END_IMPLEMENTATION

static void lua_report_error(lua_State*L)
{
    const char *msg = lua_tostring(L, -1);
    printf("%s", msg);
    lua_pop(L, 1);
}

static enum sge_script_type lua_get_type()
{
    return sge_script_lua;
}

static void lua_destory (struct sge_script_obj* obj)
{
    VIRTUAL_CONTAINER(pobj, obj, struct sge_lua_obj);

    lua_close(pobj->l);
    sge_free(pobj);
}

static sge_bool lua_exec_file(struct sge_script_obj* obj, const char* file)
{
    VIRTUAL_CONTAINER(pobj, obj, struct sge_lua_obj);
    lua_State* l = pobj->l;

    int status = luaL_loadfile(l, file);
    if(!status)
        status = lua_pcall(l, 0, LUA_MULTRET, 0);
    else
        lua_report_error(l);
    return !status;
}

static sge_bool lua_exec_buffer(struct sge_script_obj* obj, const char* buffer)
{
    VIRTUAL_CONTAINER(pobj, obj, struct sge_lua_obj);
    lua_State* l = pobj->l;

    int status = luaL_loadbuffer(l, buffer, strlen(buffer), buffer);
    if(!status)
        status = lua_pcall(l, 0, LUA_MULTRET, 0);
    else
        lua_report_error(l);
    return !status;
}

static sge_int32 lua_call_func(struct sge_script_obj* obj, const char* name)
{
    VIRTUAL_CONTAINER(pobj, obj, struct sge_lua_obj);
    lua_State* l = pobj->l;

    lua_getglobal(l, name);
    if(lua_pcall(l,0,0,0))
    {
        lua_report_error(l);
    }
    return 0;
}

static void* lua_get_native(struct sge_script_obj* obj)
{
    VIRTUAL_CONTAINER(pobj, obj, struct sge_lua_obj);
    return pobj->l;
}
BEGIN_VTABLE_INSTANCE(sge_lua_obj, sge_script_obj)
    lua_get_type,
    lua_destory,
    lua_exec_file,
    lua_exec_buffer,
    lua_call_func,
    lua_get_native
END_VTABLE_INSTANCE

struct sge_script_obj* sge_create_lua_script()
{
    CREATE_INSTANCE(ret, sge_lua_obj, sge_malloc);
    ret->l = luaL_newstate();
    luaL_openlibs(ret->l);

    return GET_INTERFACE(ret);
}
