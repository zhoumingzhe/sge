#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "basedefine/utility.h"
#include "script_internal.h"
#include "memory/sge_memory.h"

struct sge_lua_obj
{
    struct sge_script_obj obj;
    lua_State *l;
};

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

static const struct sge_script_obj_table lua_vptr =
{
    lua_get_type,
    lua_destory
};

struct sge_script_obj* sge_create_lua_script()
{
    struct sge_lua_obj * ret;

    ret = (struct sge_lua_obj *)sge_malloc(sizeof(struct sge_lua_obj));
    ret->obj.vptr = &lua_vptr;
    ret->l = luaL_newstate();

    return &ret->obj;
}
