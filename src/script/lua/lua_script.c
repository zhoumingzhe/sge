#include <malloc.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "basedefine/utility.h"
#include "script_internal.h"
typedef struct sge_lua_obj
{
    sge_script_obj obj;
    lua_State *l;
}sge_lua_obj;

static sge_script_type lua_get_type()
{
    return sge_script_lua;
}

static void lua_destory (sge_script_obj* obj)
{
    sge_lua_obj* pobj = get_container(obj, sge_lua_obj, obj);

    lua_close(pobj->l);
    free(pobj);
}

static const struct sge_script_obj_table lua_vptr =
{
    lua_get_type,
    lua_destory
};

struct sge_script_obj* sge_create_lua_script()
{
    sge_lua_obj * ret;

    ret = (sge_lua_obj *)malloc(sizeof(sge_lua_obj));
    ret->obj.vptr = &lua_vptr;
    ret->l = luaL_newstate();

    return &ret->obj;
}