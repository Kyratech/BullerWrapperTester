#ifndef CYLINDER_MESH_H
#define CYLINDER_MESH_H

#include "Tester.h"

static std::vector<struct Vertex> getCylinderVertices(float depth, float height, float width)
{
	float halfHeight = height / 2.0;
	float halfDepth = depth / 2.0;
	float halfWidth = width / 2.0;
	float sin45 = sqrt(2) / 2.0;	//sin(45)

	std::vector<struct Vertex> cylinderVerts = {
		//Top face
		{{0.0,					halfHeight,	0.0},					{0.0,	1.0,	0.0}},	//Top centre		0
		{{halfDepth,			halfHeight,	0.0},					{0.0,	1.0,	0.0}},	//Top 12.00 (front)	1
		{{halfDepth * sin45,	halfHeight,	halfWidth * sin45},		{0.0,	1.0,	0.0}},	//Top 01:30			2
		{{0,					halfHeight, halfWidth},				{0.0,	1.0,	0.0}},	//Top 03:00			3
		{{-halfDepth * sin45,	halfHeight,	halfWidth * sin45},		{0.0,	1.0,	0.0}},	//Top 04:30			4
		{{-halfDepth,			halfHeight,	0.0},					{0.0,	1.0,	0.0}},	//Top 06.00 (back)	5
		{{-halfDepth * sin45,	halfHeight,	-halfWidth * sin45},	{0.0,	1.0,	0.0}},	//Top 07:30			6
		{{0,					halfHeight, -halfWidth},			{0.0,	1.0,	0.0}},	//Top 09:00			7
		{{halfDepth * sin45,	halfHeight,	-halfWidth * sin45},	{0.0,	1.0,	0.0}},	//Top 10:30			8

		//Curved surface
		{{halfDepth,			halfHeight,		0.0},					{1.0,	0.0,	0.0}},	//Top 12.00		9
		{{halfDepth,			-halfHeight,	0.0},					{1.0,	0.0,	0.0}},	//Bottom 12.00	10
		{{halfDepth * sin45,	halfHeight,		halfWidth * sin45},		{sin45,	0.0,	sin45}},	//Top 01:30		11
		{{halfDepth * sin45,	-halfHeight,	halfWidth * sin45},		{sin45,	0.0,	sin45}},	//Bottom 01:30	12
		{{0,					halfHeight,		halfWidth},				{0.0,	0.0,	1.0}},	//Top 03:00		13
		{{0,					-halfHeight,	halfWidth},				{0.0,	0.0,	1.0}},	//Bottom 03:00	14
		{{-halfDepth * sin45,	halfHeight,		halfWidth * sin45},		{-sin45,	0.0,	sin45}},	//Top 04:30		15
		{{-halfDepth * sin45,	-halfHeight,	halfWidth * sin45},		{-sin45,	0.0,	sin45}},	//Bottom 04:30	16
		{{-halfDepth,			halfHeight,		0.0},					{-1.0,	0.0,	0.0}},	//Top 06.00		17
		{{-halfDepth,			-halfHeight,	0.0},					{-1.0,	0.0,	0.0}},	//Bottom 06.00	18
		{{-halfDepth * sin45,	halfHeight,		-halfWidth * sin45},	{-sin45,	0.0,	-sin45}},	//Top 07:30		19
		{{-halfDepth * sin45,	-halfHeight,	-halfWidth * sin45},	{-sin45,	0.0,	-sin45}},	//Bottom 07:30	20
		{{0,					halfHeight,		-halfWidth},			{0.0,	0.0,	-1.0}},	//Top 09:00		21
		{{0,					-halfHeight,	-halfWidth},			{0.0,	0.0,	-1.0}},	//Bottom 09:00	22
		{{halfDepth * sin45,	halfHeight,		-halfWidth * sin45},	{sin45,	0.0,	-sin45}},	//Top 10:30		23
		{{halfDepth * sin45,	-halfHeight,	-halfWidth * sin45},	{sin45,	0.0,	-sin45}},	//Bottom 10:30	24

		//Bottom face
		{{0.0,					-halfHeight,	0.0},					{0.0,	-1.0,	0.0}},	//Bottom centre	25
		{{halfDepth,			-halfHeight,	0.0},					{0.0,	-1.0,	0.0}},	//Bottom 12.00	26
		{{halfDepth * sin45,	-halfHeight,	halfWidth * sin45},		{0.0,	-1.0,	0.0}},	//Bottom 01:30	27
		{{0,					-halfHeight,	halfWidth},				{0.0,	-1.0,	0.0}},	//Bottom 03:00	28
		{{-halfDepth * sin45,	-halfHeight,	halfWidth * sin45},		{0.0,	-1.0,	0.0}},	//Bottom 04:30	29
		{{-halfDepth,			-halfHeight,	0.0},					{0.0,	-1.0,	0.0}},	//Bottom 06.00	30
		{{-halfDepth * sin45,	-halfHeight,	-halfWidth * sin45},	{0.0,	-1.0,	0.0}},	//Bottom 07:30	31
		{{0,					-halfHeight,	-halfWidth},			{0.0,	-1.0,	0.0}},	//Bottom 09:00	32
		{{halfDepth * sin45,	-halfHeight,	-halfWidth * sin45},	{0.0,	-1.0,	0.0}},	//Bottom 10:30	33
	};

	return cylinderVerts;
}

/*
* Produces list of indices for OpenGL to construct a cylinder from the above vertex locations
* Note that this implementation depends on the order of vertices above
*/
static std::vector<GLuint> getCylinderIndices()
{
	std::vector<GLuint> cylinderInds = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 6, 7,
		0, 7, 8,
		0, 8, 1,	//Top
		9, 10, 11,
		10, 11, 12,
		11, 12, 13,
		12, 13, 14,
		13, 14, 15,
		14, 15, 16,
		15, 16, 17,
		16, 17, 18,
		17, 18, 19,
		18, 19, 20,
		19, 20, 21,
		20, 21, 22,
		21, 22, 23,
		22, 23, 24,
		23, 24, 9,
		24, 9, 10,	//Curved side
		25, 26, 27,
		25, 27, 28,
		25, 28, 29,
		25, 29, 30,
		25, 30, 31,
		25, 31, 32,
		25, 32, 33,
		25, 33, 26	//Bottom
	};

	return cylinderInds;
}

#endif