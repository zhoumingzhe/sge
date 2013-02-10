#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "runtime_assert.h"

static int default_runtime_assert_output(const char *format,...)
{
    int ret = 0;
    va_list ap;
    va_start(ap, format);
    ret = vfprintf(stderr, format, ap);
    va_end(ap);
    return ret;
}

static int (*runtime_assert_output)(const char *format,...) = default_runtime_assert_output;


void _sge_runtime_assert(int expr, const char* msg, int line, const char* file)
{
    if(!expr)
    {
        runtime_assert_output("runtime assertion failed: %s, at file %s(%d)", msg, file, line);
        abort();
    }
}

