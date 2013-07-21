#include <stdlib.h>
#include "sge_memory.h"
#include "basedefine/utility.h"
#define SGE_MALLOC_ALIGN 16
void* sge_malloc(sge_size_t size)
{
    void* p = malloc(size + SGE_MALLOC_ALIGN);
    void* pret = (void*)align_up((sge_size_t)p+1, SGE_MALLOC_ALIGN);
    *((sge_uint8*)pret-1) = (sge_uint8)((sge_uint8*)pret - (sge_uint8*)p);
    return pret;
}
void sge_free(void* mem)
{
    void* p = (sge_uint8*)mem - *((sge_uint8*)mem-1);
    free(p);
}

