#ifndef SCRIPT_SCRIPT_H
#define SCRIPT_SCRIPT_H

typedef struct sge_script_obj sge_script_obj;
typedef enum sge_script_type
{
    sge_script_lua
}sge_script_type;

sge_script_obj* sge_create_lua_script();
sge_script_type sge_get_script_type(sge_script_obj* obj);
void sge_destory_script(sge_script_obj* obj);

#endif