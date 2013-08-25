#ifndef SCRIPT_SCRIPT_INTERNAL_H
#define SCRIPT_SCRIPT_INTERNAL_H
#include "script.h"
#include <basedefine/polymorphic.h>

BEGIN_VTABLE(sge_script_obj)
    enum sge_script_type (* get_type)();
    void (* destory)(struct sge_script_obj*);
    sge_bool (* exec_file)(struct sge_script_obj*, const char*);
    sge_bool (* exec_buffer)(struct sge_script_obj*, const char*);
    sge_int32 (* call_func)(struct sge_script_obj*, const char*);
    void* (*get_native)(struct sge_script_obj*);
END_VTABLE(sge_script_obj)

#endif
