#ifndef BASEDEFINE_RUNTIME_ASSERT_H
#define BASEDEFINE_RUNTIME_ASSERT_H
#include "platform.h"
SGE_EXTERN_C_START
typedef int (*sge_runtime_assert_output_func)(const char *format,...);
sge_runtime_assert_output_func sge_set_runtime_assert_output(sge_runtime_assert_output_func);
void _sge_runtime_assert(int expr, const char* msg, int line, const char* file);
SGE_EXTERN_C_END
#define sge_runtime_assert(expr) _sge_runtime_assert(expr, #expr, __LINE__, __FILE__)
#define sge_runtime_assert_msg(expr, msg) _sge_runtime_assert(expr, msg, __LINE__, __FILE__)

#endif