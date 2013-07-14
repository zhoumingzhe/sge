#ifndef RENDERSYS_RENDERCONTEXT_H
#define RENDERSYS_RENDERCONTEXT_H
#include "basedefine/types.h"
struct sge_render_context;

SGE_EXTERN_C_START

void sge_render_context_present(struct sge_render_context*);
void sge_render_context_destroy(struct sge_render_context*);

SGE_EXTERN_C_START
#endif