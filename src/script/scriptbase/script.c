#include "script.h"
#include "script_internal.h"

enum sge_script_type sge_get_script_type(struct sge_script_obj* obj)
{
    return VTABLE_CALL(obj, get_type)();
}

void sge_destory_script(struct sge_script_obj* obj)
{
    VTABLE_CALL(obj, destory)(obj);
}

sge_bool sge_exec_file(struct sge_script_obj* obj, const char* name)
{
    return VTABLE_CALL(obj, exec_file)(obj, name);
}

sge_bool sge_exec_buffer(struct sge_script_obj* obj, const char* buffer)
{
    return VTABLE_CALL(obj, exec_buffer)(obj, buffer);
}

sge_int32 sge_call_func( struct sge_script_obj* obj, const char* name )
{
    return VTABLE_CALL(obj,call_func)(obj, name);
}

void* sge_get_native_script_interface( struct sge_script_obj* obj )
{
    return VTABLE_CALL(obj, get_native)(obj);
}
