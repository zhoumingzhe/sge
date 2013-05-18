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

void sge_exec_buffer(struct sge_script_obj* obj, const char* buffer)
{
	obj->vptr->exec_buffer(buffer);
}
