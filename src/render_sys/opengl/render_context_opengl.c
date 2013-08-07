#include "render_context_opengl.h"
#include "basedefine/utility.h"
#define GLEW_STATIC
#include <GL/glew.h>

static void init_opengl_context_state_cache(struct sge_render_context_state_cache *cache)
{
    cache->clear_color = sge_vec4f_zero();
    cache->clear_depth = 1.0f;
    cache->clear_stencil = 0;
}
void init_opengl_context(struct sge_render_context_opengl* context)
{
    init_opengl_context_state_cache(&context->cache);
}

void opengl_context_clear(struct sge_render_context* context, sge_int32 mask,
                          sge_vec4f color, sge_float32 depth, sge_int32 stencil)
{
    struct sge_render_context_opengl* context_opengl =
        get_container(context, struct sge_render_context_opengl, render_context_base);

    sge_int32 glclearmask = 0;

    if(mask & clear_color)
    {
        glclearmask |= GL_COLOR_BUFFER_BIT;
        if(!sge_vec4f_eql(context_opengl->cache.clear_color, color))
        {
            sge_vec4f_aligned colorarray;
            sge_vec4f_store_aligned(colorarray, color);
            glClearColor(colorarray[0], colorarray[1], colorarray[2], colorarray[3]);
            context_opengl->cache.clear_color = color;
        }
    }

    if(mask & clear_depth)
    {
        glclearmask |= GL_DEPTH_BUFFER_BIT;
        if(context_opengl->cache.clear_depth != depth)
        {
            glClearDepth(depth);
            context_opengl->cache.clear_depth = depth;
        }
    }

    if(mask & clear_stencil)
    {
        glclearmask |= GL_STENCIL_BUFFER_BIT;
        if(context_opengl->cache.clear_stencil != stencil)
        {
            glClearStencil(stencil);
            context_opengl->cache.clear_stencil = stencil;
        }
    }

    glClear(glclearmask);
}
