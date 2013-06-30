typedef float vec3[3];
typedef float vec2[2];

vec3 vCubeVertices[] = 
{
	// Front face
	{-0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f}, {-0.5f, -0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f},
	// Back face
	{0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, -0.5f},
	// Left face
	{-0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, 0.5f}, {-0.5f, -0.5f, 0.5f}, {-0.5f, -0.5f, 0.5f}, {-0.5f, -0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f},
	// Right face
	{0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, 0.5f}, {0.5f, 0.5f, 0.5f},
	// Top face
	{-0.5f, 0.5f, -0.5f}, {0.5f, 0.5f, -0.5f}, {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, -0.5f},
	// Bottom face
	{-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f},
};
vec2 vCubeTexCoords[] = {{0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f}};

vec3 vPyramidVertices[] = 
{
	// Front face
	{0.0f, 0.5f, 0.0f}, {-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f},
	// Back face
	{0.0f, 0.5f, 0.0f}, {0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
	// Left face
	{0.0f, 0.5f, 0.0f}, {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f},
	// Right face
    {0.0f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f}
};

vec2 vPyramidTexCoords[] = {{0.5f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}};

vec3 vGround[] = 
{
    {-50, -10, -50}, {50, -10, -50}, {50, -10, 50}, {50, -10, 50}, {-50, -10, 50}, {-50, -10, -50}
};