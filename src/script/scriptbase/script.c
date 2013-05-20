#include "script.h"
#include "script_internal.h"

enum sge_script_type sge_get_script_type(struct sge_script_obj* obj)
{
    return obj->vptr->get_type();
}

void sge_destory_script(struct sge_script_obj* obj)
{
    obj->vptr->destory(obj);
}

sge_bool sge_exec_file(struct sge_script_obj* obj, const char* buffer)
{
    return obj->vptr->exec_file(obj, buffer);
}

sge_bool sge_exec_buffer(struct sge_script_obj* obj, const char* buffer)
{
    return obj->vptr->exec_buffer(obj, buffer);
}

void* sge_get_native_interface( struct sge_script_obj* obj )
{
    return obj->vptr->get_native(obj);
}
