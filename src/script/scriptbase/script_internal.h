#ifndef SCRIPT_SCRIPT_INTERNAL_H
#define SCRIPT_SCRIPT_INTERNAL_H
#include "script.h"
struct sge_script_obj_table;
struct sge_script_obj
{
    const struct sge_script_obj_table * vptr;
};

struct sge_script_obj_table
{
    enum sge_script_type (* get_type)();
    void (* destory)(struct sge_script_obj*);
};

#endif
