#ifndef SCRIPT_SCRIPT_H
#define SCRIPT_SCRIPT_H
#include "basedefine/types.h"
SGE_EXTERN_C_START
struct sge_script_obj; 
enum sge_script_type
{
    sge_script_lua
};

struct sge_script_obj* sge_create_lua_script();

enum sge_script_type sge_get_script_type(struct sge_script_obj* obj);
void sge_destory_script(struct sge_script_obj* obj);
sge_bool sge_exec_file(struct sge_script_obj* obj, const char* name);
sge_bool sge_exec_buffer(struct sge_script_obj* obj, const char* buffer);
sge_int32 sge_call_func(struct sge_script_obj* obj, const char* name);
void* sge_get_native_interface(struct sge_script_obj* obj);
SGE_EXTERN_C_START
#endif
