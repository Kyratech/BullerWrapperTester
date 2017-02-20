#ifndef CONE_MESH
#define CONE_MESH

#include "Tester.h"

/*
  Get the vertex locations for a cone centred on the Y axis
  The cone has 8 sides on the curved face (it has to work, not look good, dammit!)
*/
static std::vector<struct Vertex> getConeVertices(float height, float radius)
{
	float halfHeight = height / 2.0;
	float sinRadius = radius * sqrt(2) / 2.0;	//Radius * sin(45)
	float hypotenuse = sqrt(radius * radius + height * height);

	std::vector<struct Vertex> coneVerts = {
		//Base
		{{0.0f,			-halfHeight,	0.0f},			{0.0f,	-1.0f,	0.0f}},	//Bottom middle
		{{radius,		-halfHeight,	0.0f},			{0.0f,	-1.0f,	0.0f}},	//Bottom 12:00 (front)
		{{sinRadius,	-halfHeight,	sinRadius},		{0.0f,	-1.0f,	0.0f}},	//Bottom 01:30
		{{0.0f,			-halfHeight,	radius},		{0.0f,	-1.0f,	0.0f}},	//Bottom 03:00
		{{-sinRadius,	-halfHeight,	sinRadius},		{0.0f,	-1.0f,	0.0f}},	//Bottom 04:30
		{{-radius,		-halfHeight,	0.0f},			{0.0f,	-1.0f,	0.0f}},	//Bottom 06:00 (back)
		{{-sinRadius,	-halfHeight,	-sinRadius},	{0.0f,	-1.0f,	0.0f}},	//Bottom 07:30
		{{0.0f,			-halfHeight,	-radius},		{0.0f,	-1.0f,	0.0f}},	//Bottom 09:00
		{{sinRadius,	-halfHeight,	-sinRadius},	{0.0f,	-1.0f,	0.0f}},	//Bottom 10:30

		//Curved surface
		{{0.0f,			halfHeight,		0.0f},			{radius * height / hypotenuse,		radius / hypotenuse,	0.0f}},								//Top 12:00		9
		{{radius,		-halfHeight,	0.0f},			{radius * height / hypotenuse,		radius / hypotenuse,	0.0f}},								//Bottom 12:00	10
		{{0.0f,			halfHeight,		0.0f},			{sinRadius * height / hypotenuse,	radius / hypotenuse,	sinRadius * height / hypotenuse}},	//Top 01:30		11
		{{sinRadius,	-halfHeight,	sinRadius},		{sinRadius * height / hypotenuse,	radius / hypotenuse,	sinRadius * height / hypotenuse}},	//Bottom 01:30	12
		{{0.0f,			halfHeight,		0.0f},			{0.0f,								radius / hypotenuse,	radius * height / hypotenuse}},		//Top 03:00		13
		{{0.0f,			-halfHeight,	radius},		{0.0f,								radius / hypotenuse,	radius * height / hypotenuse}},		//Bottom 03:00	14
		{{0.0f,			halfHeight,		0.0f},			{-sinRadius * height / hypotenuse,	radius / hypotenuse,	sinRadius * height / hypotenuse}},	//Top 04:30		15
		{{-sinRadius,	-halfHeight,	sinRadius},		{-sinRadius * height / hypotenuse,	radius / hypotenuse,	sinRadius * height / hypotenuse}},	//Bottom 04:30	16
		{{0.0f,			halfHeight,		0.0f},			{-radius * height / hypotenuse,		radius / hypotenuse,	0.0f}},								//Top 06:00		17
		{{-radius,		-halfHeight,	0.0f},			{-radius * height / hypotenuse,		radius / hypotenuse,	0.0f}},								//Bottom 06:00	18
		{{0.0f,			halfHeight,		0.0f},			{-sinRadius * height / hypotenuse,	radius / hypotenuse,	-sinRadius * height / hypotenuse}},	//Top 07:30		19
		{{-sinRadius,	-halfHeight,	-sinRadius},	{-sinRadius * height / hypotenuse,	radius / hypotenuse,	-sinRadius * height / hypotenuse}},	//Bottom 07:30	20
		{{0.0f,			halfHeight,		0.0f},			{0.0f,								radius / hypotenuse,	-radius * height / hypotenuse}},		//Top 09:00		21
		{{0.0f,			-halfHeight,	-radius},		{0.0f,								radius / hypotenuse,	-radius * height / hypotenuse}},		//Bottom 09:00	22
		{{0.0f,			halfHeight,		0.0f},			{sinRadius * height / hypotenuse,	radius / hypotenuse,	-sinRadius * height / hypotenuse}},	//Top 10:30		23
		{{sinRadius,	-halfHeight,	-sinRadius},	{sinRadius * height / hypotenuse,	radius / hypotenuse,	-sinRadius * height / hypotenuse}},	//Bottom 10:30	24
	};

	return coneVerts;
}

/*
* Produces list of indices for OpenGL to construct a cone from the above vertex locations
* Note that this implementation depends on the order of vertices above
*/
static std::vector<GLuint> getConeIndices()
{
	std::vector<GLuint> coneInds = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 6, 7,
		0, 7, 8,
		0, 8, 1, //Base
		9, 10, 12,
		11, 12, 14,
		13,	14, 16,
		15, 16, 18,
		17, 18, 20,
		19, 20, 22,
		21, 22, 24,
		23, 24,	10	//Curved surface
	};

	return coneInds;
}

#endif