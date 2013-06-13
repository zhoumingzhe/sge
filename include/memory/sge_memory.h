#ifndef SGE_MEMORY_H
#define SGE_MEMORY_H

#include "../basedefine/types.h"
SGE_EXTERN_C_START
void* sge_malloc(sge_size_t size);
void sge_free(void* mem);
SGE_EXTERN_C_END
#endif
