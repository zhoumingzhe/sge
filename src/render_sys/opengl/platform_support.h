#ifndef RENDERSYS_PLATFORMSUPPORT_H
#define RENDERSYS_PLATFORMSUPPORT_H
struct sge_render_sys;
struct sge_window_obj;

sge_bool init_glew();
struct sge_render_context* create_context(struct sge_render_sys*, struct sge_window_obj*);
#endif