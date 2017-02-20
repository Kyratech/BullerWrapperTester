#ifndef WRAPPER_TESTER_H
#define WRAPPER_TESTER_H

//GL stuff
#include <GL/glew.h>

//GLM - Maths for openGL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Other
#include <vector>
#include <math.h>

struct Vertex
{
	GLfloat position[3];
	GLfloat normals[3];
};

#endif