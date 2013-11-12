#pragma once

/********************************

Class:	CVertexBufferObject

Purpose:	Wraps OpenGL vertex buffer
			object.

********************************/

#include <vector>
class CVertexBufferObject
{
public:
	void createVBO(int a_iSize = 0);
	void releaseVBO();


	void bindVBO(int a_iBufferType = GL_ARRAY_BUFFER);
	void uploadDataToGPU(int iUsageHint);
	
	void addData(void* ptrData, UINT uiDataSize);


	CVertexBufferObject();

private:
	UINT uiBuffer;
	int iSize;
	int iBufferType;
	vector<BYTE> data;

	bool bDataUploaded;
};