#ifndef SCRIPT_SCRIPT_H
#define SCRIPT_SCRIPT_H
#include "basedefine/types.h"
struct sge_script_obj; 
enum sge_script_type
{
    sge_script_lua
};

struct sge_script_obj* sge_create_lua_script();

enum sge_script_type sge_get_script_type(struct sge_script_obj* obj);
void sge_destory_script(struct sge_script_obj* obj);
sge_bool sge_exec_file(struct sge_script_obj* obj, const char* buffer);
sge_bool sge_exec_buffer(struct sge_script_obj* obj, const char* buffer);
void* sge_get_native_interface(struct sge_script_obj* obj);
#endif
