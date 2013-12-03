#include "render_headers_opengl.h"
#include "render_context_opengl.h"
#include "render_vertex_buffer_opengl.h"
#include "basedefine/utility.h"
#include "basedefine/polymorphic.h"
#include "basedefine/static_assert.h"
#include "memory/sge_memory.h"

static void init_opengl_context_state_cache(struct sge_render_context_state_cache *cache)
{
    cache->clear_color = sge_vec4f_zero();
    cache->clear_depth = 1.0f;
    cache->clear_stencil = 0;
    cache->depth_test_enable = sge_false;
}

void init_opengl_context(struct sge_render_context_opengl* context)
{
    init_opengl_context_state_cache(&context->cache);
    sge_list_init(&context->vertex_list);
}

void opengl_context_clear(struct sge_render_context* context, sge_int32 mask,
                          sge_vec4f color, sge_float32 depth, sge_int32 stencil)
{
    VIRTUAL_CONTAINER(context_opengl, context, struct sge_render_context_opengl);

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

struct sge_render_vertex_buffer* opengl_create_vertex_buffer(
    struct sge_render_context* context, sge_uint32 size, void* buffer, enum sge_vb_usage flag,
    sge_uint32 stride)
{
    VIRTUAL_CONTAINER(context_opengl, context, struct sge_render_context_opengl);

    struct sge_render_vertex_buffer_opengl* vertex_buffer = create_vertex_buffer_opengl(
    context_opengl, size, buffer, flag, stride);

    return GET_INTERFACE(vertex_buffer);
}

void opengl_enable_depth_test(struct sge_render_context* context, sge_bool enable)
{
    VIRTUAL_CONTAINER(context_opengl, context, struct sge_render_context_opengl);
    if (context_opengl->cache.depth_test_enable != enable)
    {
        if (enable)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
        context_opengl->cache.depth_test_enable = enable;
    }
}

static GLenum primitive_topo[] =
{
    GL_TRIANGLES,
    GL_TRIANGLE_FAN,
    GL_TRIANGLE_STRIP
};

sge_static_assert(sizeof(primitive_topo) / sizeof(primitive_topo[0]) == sge_pt_end, primitive_topology_equal);
void opengl_draw(struct sge_render_context* context, enum sge_primitive_type type, sge_int32 start, sge_int32 count)
{
    glDrawArrays(primitive_topo[type], start, count*3);
}
