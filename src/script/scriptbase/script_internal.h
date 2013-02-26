#ifndef SCRIPT_SCRIPT_INTERNAL_H
#define SCRIPT_SCRIPT_INTERNAL_H
#include "script.h"
typedef struct sge_script_obj_table sge_script_obj_table;
typedef struct sge_script_obj
{
    const sge_script_obj_table * vptr;
}sge_script_obj;

typedef struct sge_script_obj_table
{
    enum sge_script_type (* get_type)();
    void (* destory)(struct sge_script_obj*);
}sge_script_obj_table;

#endif