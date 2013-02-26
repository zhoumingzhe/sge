#include "script.h"
#include "script_internal.h"

sge_script_type sge_get_script_type(struct sge_script_obj* obj)
{
    return obj->vptr->get_type();
}

void sge_destory_script(struct sge_script_obj* obj)
{
    obj->vptr->destory(obj);
}
