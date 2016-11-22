#ifndef PLANE_MESH_H
#define PLANE_MESH_H

//GL stuff
#include <GL/glew.h>

//GLM - Maths for openGL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Other
#include <vector>

/*
* Produces a vector of vertex locations for constructing a square plane
* It sits in the XY plane
*/
static std::vector<GLfloat> getXYPlaneVertices(float sideLength)
{
	//Centred around local (0,0), the vertices have xy locations at +/- half the side length
	float halfSide = sideLength / 2;

	std::vector<GLfloat> planeVerts = {
		-halfSide,	-halfSide,	0.0f,	0.0f,	0.0f,	1.0f,	//Bottom left
		halfSide,	-halfSide,	0.0f,	0.0f,	0.0f,	1.0f,	//Bottom right
		halfSide,	halfSide,	0.0f,	0.0f,	0.0f,	1.0f,	//Top right
		-halfSide,	halfSide,	0.0f,	0.0f,	0.0f,	1.0f,	//Top left
	};

	return planeVerts;
}

/*
* Produces a vector of vertex locations for constructing a square plane
* It sits in the XZ plane
*/
static std::vector<GLfloat> getXZPlaneVertices(float sideLength)
{
	//Centred around local (0,0), the vertices have xy locations at +/- half the side length
	float halfSide = sideLength / 2;

	std::vector<GLfloat> planeVerts = {
		-halfSide,	0.0f,	-halfSide,	0.0f,	1.0f,	0.0f,	//Bottom left
		halfSide,	0.0f, 	-halfSide,	0.0f,	1.0f,	0.0f,	//Bottom right
		halfSide,	0.0f, 	halfSide,	0.0f,	1.0f,	0.0f,	//Top right
		-halfSide,	0.0f,	halfSide,	0.0f,	1.0f,	0.0f,	//Top left
	};

	return planeVerts;
}

/*
* Produces list of indices for OpenGL to construct a plane from the above vertex locations
* Note that this implementation depends on the order of vertices above
*/
static std::vector<GLuint> getPlaneIndices()
{
	std::vector<GLuint> cubeInds = {
		0, 1, 3,
		1, 3, 2,	//Front
	};

	return cubeInds;
}

#endif