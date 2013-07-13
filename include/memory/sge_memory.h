#ifndef SGE_MEMORY_H
#define SGE_MEMORY_H

#ifdef memory_EXPORTS
#define memory_API sge_export
#else
#define memory_API sge_import
#endif

#include "../basedefine/types.h"
SGE_EXTERN_C_START
memory_API void* sge_malloc(sge_size_t size);
memory_API void sge_free(void* mem);
SGE_EXTERN_C_END
#endif
