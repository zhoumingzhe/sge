#pragma once

#define SIMPLE_OPENGL_CLASS_NAME "simple_openGL_class_name"

/********************************

Class:	COpenGLControl

Purpose:	Provides convenient usage
			of OpenGL

********************************/

class COpenGLControl
{
public:
	bool initOpenGL(HINSTANCE hInstance, HWND* a_hWnd, int iMajorVersion, int iMinorVersion, void (*a_initScene)(LPVOID), void (*a_renderScene)(LPVOID), void(*a_releaseScene)(LPVOID), LPVOID lpParam);
	
	void resizeOpenGLViewportFull();
	void setProjection3D(float width, float height, float fNear, float fFar);
	sge_mat44f* getProjectionMatrix();

	void render(LPVOID lpParam);
	void releaseOpenGLControl(LPVOID lpParam);

	static void registerSimpleOpenGLClass(HINSTANCE hInstance);
	static void unregisterSimpleOpenGLClass(HINSTANCE hInstance);

	void makeCurrent();
	void swapBuffers();

	bool setVerticalSynchronization(bool bEnabled);

	COpenGLControl();

private:
	bool initGLEW(HINSTANCE hInstance);

	HDC hDC;
	HWND* hWnd;
	HGLRC hRC;
	static bool bClassRegistered;
	static bool bGlewInitialized;
	int iMajorVersion, iMinorVersion;

	// Matrix for perspective projection
	sge_mat44f mProjection;

	void (*initScene)(LPVOID lpParam), (*renderScene)(LPVOID lpParam), (*releaseScene)(LPVOID lpParam);
};

LRESULT CALLBACK msgHandlerSimpleOpenGLClass(HWND, UINT, WPARAM, LPARAM);