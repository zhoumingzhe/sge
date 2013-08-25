#ifndef BASEDEFINE_POLYMORPHIC_H
#define BASEDEFINE_POLYMORPHIC_H

#include "types.h"

//define virtual function table
#define BEGIN_VTABLE(base)\
struct _##base##_vtable{

#define END_VTABLE(base) };\
struct base\
{\
    const struct _##base##_vtable* vt;\
};

//translate C function call to virtual function call
#define VTABLE_CALL(object, method)\
    object->vt->method

//implementation the interface
#define BEGIN_IMPLEMENTATION(type, base)\
struct type\
{\
struct base _father;

#define END_IMPLEMENTATION };

#define VIRTUAL_CONTAINER(p, address, type)\
    type* p = (type*)((sge_uint8*)(address)-(sge_uint8*)(&((type*)0)->_father))

//define virtual function table
#define BEGIN_VTABLE_INSTANCE(type, base)\
    static const struct _##base##_vtable _##type##_vtable = {

#define END_VTABLE_INSTANCE };

#define CREATE_INSTANCE(ptr, type, allocate)\
struct type* ptr = (struct type*)allocate(sizeof(struct type));\
    ptr->_father.vt = &_##type##_vtable

#define GET_INTERFACE(ptr)\
    &ptr->_father

#endif