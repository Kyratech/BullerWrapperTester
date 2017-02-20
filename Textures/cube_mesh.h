#ifndef CUBE_MESH_H
#define CUBE_MESH_H

#include "Tester.h"

/*
* Produces a vector of vertex locations for constructing a cube
* Cube is centred around local origin
		 ____________
		/|			/|			y
	   / |		   / |			^	z
	  /	 |		  /	 |			|  ¬
	 /___________/   |			| /
	|	 |__O___|____|			|/____> x
	|	/		|	/			O
	|  /		|  /
	| /			| /
	|/__________|/
		
*/
static std::vector<struct Vertex> getCubeVertices(float sideLength)
{
	//Centred around local (0,0), the vertices have xyz locations at +/- half the side length
	float halfSide = sideLength / 2.0;

	std::vector<struct Vertex> cubeVerts = {
		//Front
		{{-halfSide,	-halfSide,	-halfSide},	{0.0f, 0.0f, -1.0f}},	//Front bottom left
		{{halfSide,		-halfSide,	-halfSide},	{0.0f, 0.0f, -1.0f}},	//Front bottom right
		{{halfSide,		halfSide,	-halfSide},	{0.0f, 0.0f, -1.0f}},	//Front top right
		{{-halfSide,	halfSide,	-halfSide},	{0.0f, 0.0f, -1.0f}},	//Front top left

		//Right
		{{halfSide,	-halfSide,	-halfSide},	{1.0f, 0.0f, 0.0f}},	//Front bottom right
		{{halfSide,	halfSide,	-halfSide},	{1.0f, 0.0f, 0.0f}},	//Front top right
		{{halfSide,	halfSide,	halfSide},	{1.0f, 0.0f, 0.0f}},	//Back top right
		{{halfSide,	-halfSide,	halfSide},	{1.0f, 0.0f, 0.0f}},	//Back bottom right

		//Back
		{{-halfSide,	-halfSide,	halfSide},	{0.0f, 0.0f, 1.0f}},	//Back bottom left
		{{halfSide,		-halfSide,	halfSide},	{0.0f, 0.0f, 1.0f}},	//Back bottom right
		{{halfSide,		halfSide,	halfSide},	{0.0f, 0.0f, 1.0f} },	//Back top right
		{{-halfSide,	halfSide,	halfSide},	{0.0f, 0.0f, 1.0f}},	//Back top left

		//Left
		{{-halfSide,	-halfSide,	-halfSide},	{-1.0f, 0.0f, 0.0f}},	//Front bottom left
		{{-halfSide,	-halfSide,	halfSide},	{-1.0f, 0.0f, 0.0f}},	//Back bottom left
		{{-halfSide,	halfSide,	-halfSide},	{-1.0f, 0.0f, 0.0f}},	//Front top left
		{{-halfSide,	halfSide,	halfSide},	{-1.0f, 0.0f, 0.0f}},	//Back top left
		
		//Bottom
		{{-halfSide,	-halfSide,	-halfSide},	{0.0f, -1.0f, 0.0f}},	//Front bottom left
		{{halfSide,		-halfSide,	-halfSide},	{0.0f, -1.0f, 0.0f}},	//Front bottom right
		{{-halfSide,	-halfSide,	halfSide},	{0.0f, -1.0f, 0.0f}},	//Back bottom left
		{{halfSide,		-halfSide,	halfSide},	{0.0f, -1.0f, 0.0f}},	//Back bottom right
		
		//Top
		{{halfSide,		halfSide,	-halfSide},	{0.0f, 1.0f, 0.0f}},	//Front top right
		{{-halfSide,	halfSide,	-halfSide},	{0.0f, 1.0f, 0.0f}},	//Front top left	
		{{halfSide,		halfSide,	halfSide},	{0.0f, 1.0f, 0.0f}},	//Back top right
		{{-halfSide,	halfSide,	halfSide},	{0.0f, 1.0f, 0.0f}}	//Back top left
	};

	return cubeVerts;
}

/*
* Produces list of indices for OpenGL to construct a cube from the above vertex locations
* Note that this implementation depends on the order of vertices above
*/
static std::vector<GLuint> getCubeIndices()
{
	std::vector<GLuint> cubeInds = {
		0, 1, 2,
		0, 2, 3,	//Front
		4, 5, 6,
		4, 6, 7,	//Right
		8, 9, 11,
		9, 10, 11,	//Back
		12, 13, 14,
		13, 14, 15,	//Left
		16, 17, 19,
		16, 18, 19,	//Bottom
		20, 21, 23,
		20, 22, 23	//Top
	};

	return cubeInds;
}

#endif