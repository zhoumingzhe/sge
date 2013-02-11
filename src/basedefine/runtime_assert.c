#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "runtime_assert.h"

static void default_runtime_assert_output(const char *format,...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
}

static void default_runtime_assert_exit()
{
    abort();
}

sge_runtime_assert_output_func runtime_assert_output = default_runtime_assert_output;
sge_runtime_assert_exit_func runtime_assert_exit = default_runtime_assert_exit;

sge_runtime_assert_output_func sge_set_runtime_assert_output(sge_runtime_assert_output_func f)
{
    sge_runtime_assert_output_func old = runtime_assert_output;
    runtime_assert_output = f;
    return old;
}

sge_runtime_assert_exit_func sge_set_runtime_assert_exit(sge_runtime_assert_exit_func f)
{
    sge_runtime_assert_exit_func old = runtime_assert_exit;
    runtime_assert_exit = f;
    return old;
}

void _sge_runtime_assert(int expr, const char* msg, int line, const char* file)
{
    if(!expr)
    {
        runtime_assert_output("runtime assertion failed: %s, at file %s(%d)", msg, file, line);
        runtime_assert_exit();
    }
}

