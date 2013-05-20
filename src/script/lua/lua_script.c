#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include "basedefine/utility.h"
#include "script_internal.h"
#include "memory/sge_memory.h"

struct sge_lua_obj
{
    struct sge_script_obj obj;
    lua_State *l;
};

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
    struct sge_lua_obj* pobj = get_container(obj, struct sge_lua_obj, obj);

    lua_close(pobj->l);
    sge_free(pobj);
}

static sge_bool lua_exec_file(struct sge_script_obj* obj, const char* file)
{
    struct sge_lua_obj* pobj = get_container(obj, struct sge_lua_obj, obj);
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
    struct sge_lua_obj* pobj = get_container(obj, struct sge_lua_obj, obj);
    lua_State* l = pobj->l;

    int status = luaL_loadbuffer(l, buffer, strlen(buffer), buffer);
    if(!status)
        status = lua_pcall(l, 0, LUA_MULTRET, 0);
    else
        lua_report_error(l);
    return !status;
}
static void* lua_get_native(struct sge_script_obj* obj)
{
    struct sge_lua_obj* pobj = get_container(obj, struct sge_lua_obj, obj);
    return pobj->l;
}
static const struct sge_script_obj_table lua_vptr =
{
    lua_get_type,
    lua_destory,
    lua_exec_file,
    lua_exec_buffer,
    lua_get_native
};

struct sge_script_obj* sge_create_lua_script()
{
    struct sge_lua_obj * ret = 0;
    lua_State *l = luaL_newstate();
    luaL_openlibs(l);

    ret = (struct sge_lua_obj *)sge_malloc(sizeof(struct sge_lua_obj));
    ret->obj.vptr = &lua_vptr;
    ret->l = l;

    return &ret->obj;
}
