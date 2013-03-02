#include <stdlib.h>
#include "sge_memory.h"
void* sge_malloc(sge_size_t size)
{
    return malloc(size);
}
void sge_free(void* mem)
{
    free(mem);
}

