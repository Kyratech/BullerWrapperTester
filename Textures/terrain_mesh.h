#ifndef TERRAIN_MESH_H
#define TERRAIN_MESH_H

//GL stuff
#include <GL/glew.h>

//GLM - Maths for openGL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Other
#include <vector>
#include <iostream>

static std::vector<GLfloat> getTerrainVertices(std::vector<float>* data, int dataDepth, int dataWidth, float worldDepth, float worldWidth)
{
	float depthSpacing = worldDepth / dataDepth;
	float widthSpacing = worldWidth / dataWidth;

	std::vector<GLfloat> vertices(data->size() * 6, 0);

	std::cout << "Gonna make some terrain verts." << std::endl;

	for (int i = 0; i < data->size(); i++)
	{
		int vertexStart = i * 6;
		int z = i % dataWidth;
		int x = i / dataWidth;

		//x
		vertices[vertexStart] = x * depthSpacing - worldDepth / 2;
		//y
		vertices[vertexStart + 1] = (*data)[i];
		std::cout << (*data)[i] << std::endl;
		//z
		vertices[vertexStart + 2] = z * widthSpacing - worldWidth / 2;
		//Normals are all up for now
		vertices[vertexStart + 3] = 0.0f;
		vertices[vertexStart + 4] = 1.0f;
		vertices[vertexStart + 5] = 0.0f;
	}

	std::cout << "Made some terrain verts." << std::endl;

	return vertices;
}

static std::vector<GLuint> getTerrainIndices(int dataDepth, int dataWidth)
{
	
	std::vector<GLuint> indices((dataDepth - 1) * (dataWidth - 1) * 6 + dataDepth, 0);

	std::cout << "Gonna make " << (dataDepth - 1) * (dataWidth - 1) * 6 << " terrain inds." << std::endl;

	int counter = 0;
	for (int i = 0; i < dataDepth - 1; i++)
	{
		for (int j = 0; j < dataWidth - 1; j++)
		{
			int index = j + i * dataWidth;

			std::cout << "Working on ind: " << counter << " / " << (dataDepth - 1) * (dataWidth - 1) << std::endl;

			/*   index--------index+1
					|	\		|
					|	  \		|
					|	    \	|
				index+w-------index+w+1
				We will construct (depth - 1)x(width - 1) of these squares
			 */

			indices[counter * 6]		= index;
			indices[counter * 6 + 1]	= index + dataWidth;
			indices[counter * 6 + 2]	= index + dataWidth + 1; //Triangle 1 / 2
			indices[counter * 6 + 3]	= index;
			indices[counter * 6 + 4]	= index + 1;
			indices[counter * 6 + 5]	= index + dataWidth + 1; //Triangle 2 / 2

			counter++;
		}


	}

	std::cout << "Made some terrain inds." << std::endl;

	return indices;
	
	/*
	std::vector<GLuint> test = { 0, (unsigned)dataWidth,  (unsigned)dataWidth + 1, 0, 1,  (unsigned)dataWidth + 1 };

	return test;
	*/
}

#endif