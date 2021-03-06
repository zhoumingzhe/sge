#include "common_header.h"


#include "shaders.h"
#include "texture.h"
#include "render_sys/render_context.h"
#include "render_sys/render_vertex_buffer.h"
#include "memory/sge_memory.h"
#ifdef __cplusplus
extern "C"
{
#endif
    struct sge_render_context;
    void initScene(struct sge_render_context*);
    void renderScene(struct sge_render_context*);
    void releaseScene(struct sge_render_context*);

#ifdef __cplusplus
};
#endif
struct sge_render_vertex_buffer* vboSceneObjects;
UINT uiVAO; // And one VAO

CShader shVertex, shFragment;
CShaderProgram spMain;

CTexture tGold, tSnow;

#include "static_geometry.h"

void initScene(struct sge_render_context* context)
{
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    const sge_uint32 size = 54 * (sizeof(vec3)+sizeof(vec2));
    sge_uint8* data = (sge_uint8*)sge_malloc(size);
    sge_uint32 offset = 0;



	FOR(i, 36)
	{
		memcpy(data + offset, &vCubeVertices[i], sizeof(vec3));
        offset += sizeof(vec3);
		memcpy(data + offset, &vCubeTexCoords[i%6], sizeof(vec2));
        offset += sizeof(vec2);
	}

	// Add pyramid to VBO

	FOR(i, 12)
	{
        memcpy(data + offset, &vPyramidVertices[i], sizeof(vec3));
        offset += sizeof(vec3);
        memcpy(data + offset, &vPyramidTexCoords[i % 3], sizeof(vec2));
        offset += sizeof(vec2);
	}

	// Add ground to VBO

	FOR(i, 6)
	{
        memcpy(data + offset, &vGround[i], sizeof(vec3));
        offset += sizeof(vec3);
		vCubeTexCoords[i][0] *= 5.0f;
        vCubeTexCoords[i][1] *= 5.0f;
        memcpy(data + offset, &vCubeTexCoords[i % 6], sizeof(vec2));
        offset += sizeof(vec2);
	}
    vboSceneObjects = sge_render_context_create_vertex_buffer(context, size
        , data, sge_vb_immutable, (sizeof(vec3)+sizeof(vec2)));

    sge_free(data);
    glGenVertexArrays(1, &uiVAO); // Create one VAO
    glBindVertexArray(uiVAO);
    // Add cube to VBO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3)+sizeof(vec2), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec3)+sizeof(vec2), (void*)sizeof(vec3));

	shVertex.loadShader("data\\shaders\\shader.vert", GL_VERTEX_SHADER);
	shFragment.loadShader("data\\shaders\\shader.frag", GL_FRAGMENT_SHADER);

	spMain.createProgram();
	spMain.addShaderToProgram(&shVertex);
	spMain.addShaderToProgram(&shFragment);

	spMain.linkProgram();
	spMain.useProgram();

	sge_render_context_enable_depth_test(context, sge_true);
	//glClearDepth(1.0);

	tGold.loadTexture2D("data\\textures\\golddiag.dds", true);
	tGold.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

	tSnow.loadTexture2D("data\\textures\\snow.dds", true);
	tSnow.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
	glEnable(GL_TEXTURE_2D);
}

float fRotationAngleCube = 0.0f, fRotationAnglePyramid = 0.0f;
float fCubeRotationSpeed = 0.0f, fPyramidRotationSpeed = 0.0f;
const float PIover180 = 3.1415f/180.0f;

extern "C"
{
    extern sge_mat44f mProjection;
}
void renderScene(struct sge_render_context* context)
{

	sge_render_context_clear(context, clear_depth|clear_color, sge_vec4f_zero(), 1.0f, 0);

	int iModelViewLoc = glGetUniformLocation(spMain.getProgramID(), "modelViewMatrix");
	int iProjectionLoc = glGetUniformLocation(spMain.getProgramID(), "projectionMatrix");
	glUniformMatrix4fv(iProjectionLoc, 1, GL_FALSE, &(mProjection._11));

	sge_mat44f mModelView = sge_mat44f_lookat_rh(sge_vec4f_init(0, 12, 27, 0),
        sge_vec4f_init(0, 0, 0, 0), sge_vec4f_init(0.0f, 1.0f, 0.0f, 0.0f));
	sge_mat44f mCurrent;

	glBindVertexArray(uiVAO);

	int iSamplerLoc = glGetUniformLocation(spMain.getProgramID(), "gSampler");
	glUniform1i(iSamplerLoc, 0);

	tGold.bindTexture(0);

	// Rendering of cube

    sge_mat44f trans = sge_mat44f_translate(-8.0f, 0.0f, 0.f);
    mCurrent = sge_mat44f_mul(trans, mModelView);


    sge_mat44f scale = sge_mat44f_scale(10.0f, 10.0f, 10.0f);
    mCurrent = sge_mat44f_mul(scale, mCurrent);


    sge_mat44f rotate = sge_mat44f_rotate(sge_vec4f_init(1.0f, 0.0f, 0.0f, 0.0f), fRotationAngleCube);
    mCurrent = sge_mat44f_mul(rotate, mCurrent);

	glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, &(mCurrent._11));

    sge_render_context_draw(context, sge_pt_triangle, 0, 12);

	// Rendering of pyramid

    trans = sge_mat44f_translate(8.0f, 0.0f, 0.0f);
    mCurrent = sge_mat44f_mul(trans, mModelView);


    scale = sge_mat44f_scale(10.0f, 10.0f, 10.0f);
    mCurrent = sge_mat44f_mul(scale, mCurrent);


    rotate = sge_mat44f_rotate(sge_vec4f_init(1.0f, 0.0f, 0.0f, 0.0f), fRotationAngleCube);
    mCurrent = sge_mat44f_mul(rotate, mCurrent);

	glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, &(mCurrent._11));

    sge_render_context_draw(context, sge_pt_triangle, 36, 4);

	// Render ground

	tSnow.bindTexture();

	glUniformMatrix4fv(iModelViewLoc, 1, GL_FALSE, &(mModelView._11));
	//glDrawArrays(GL_TRIANGLES, 48, 6);
    sge_render_context_draw(context, sge_pt_triangle, 48, 2);
	//oglControl->swapBuffers();
}


void releaseScene(struct sge_render_context*)
{
	spMain.deleteProgram();

	shVertex.deleteShader();
	shFragment.deleteShader();

	sge_render_vertex_buffer_destroy(vboSceneObjects);
	glDeleteVertexArrays(1, &uiVAO);

	tGold.releaseTexture();
	tSnow.releaseTexture();
}