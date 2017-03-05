#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include "Tester.h"
#include <iostream>
#include "SimpleBulletWrapper\include\TinyOBJLoader\tiny_obj_loader.h"

/*
 * Use the TinyOBJLoader packaged in the wrapper library to load a triangle mesh
 * Honestly, getting openGL indices for this is a pain in the proverbial,
 * So each vertex will be considered as separate.
*/
static std::vector<struct Vertex> GetMeshVertices(std::string filename)
{
	/* TinyOBJ setup*/
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials; //Not used

	std::string err;
	bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str());

	//Print any errors raised by the OBJ loader
	if (!err.empty())
	{
		std::cerr << err << std::endl;
	}

	//Exit application if could not load OBJ
	if (!success)
	{
		exit(1);
	}

	std::vector<Vertex> vertices;

	//Shapes
	for (size_t shape = 0; shape < shapes.size(); shape++)
	{
		//Polygon faces within a given shape
		size_t index_offset = 0;
		for (size_t face = 0; face < shapes[shape].mesh.num_face_vertices.size(); face++)
		{
			//Imported as triangles, so I -think- this should always be 3...
			//Documentation could be better
			int faceVertCount = shapes[shape].mesh.num_face_vertices[face];

			//Vertices in given face
			for (size_t vert = 0; vert < faceVertCount; vert++)
			{
				tinyobj::index_t i = shapes[shape].mesh.indices[index_offset + vert];
				float vx = attrib.vertices[3 * i.vertex_index + 0];
				float vy = attrib.vertices[3 * i.vertex_index + 1];
				float vz = attrib.vertices[3 * i.vertex_index + 2];
				float nx = attrib.normals[3 * i.normal_index + 0];
				float ny = attrib.normals[3 * i.normal_index + 1];
				float nz = attrib.normals[3 * i.normal_index + 2];
				vertices.push_back({{ vx, vy, vz },{ nx, ny, nz }});
			}
			index_offset += faceVertCount;
		}
	}

	return vertices;
}

static std::vector<GLuint> GetMeshIndices(std::string filename)
{
	/* TinyOBJ setup*/
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials; //Not used

	std::string err;
	bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str());

	//Print any errors raised by the OBJ loader
	if (!err.empty())
	{
		std::cerr << err << std::endl;
	}

	//Exit application if could not load OBJ
	if (!success)
	{
		exit(1);
	}

	std::vector<GLuint> indices;

	//Shapes
	int index = 0;
	for (size_t shape = 0; shape < shapes.size(); shape++)
	{
		//Polygon faces within a given shape
		size_t index_offset = 0;
		for (size_t face = 0; face < shapes[shape].mesh.num_face_vertices.size(); face++)
		{
			//Imported as triangles, so I -think- this should always be 3...
			//Documentation could be better
			int faceVertCount = shapes[shape].mesh.num_face_vertices[face];

			//Vertices in given face
			for (size_t vert = 0; vert < faceVertCount; vert++)
			{
				indices.push_back(index++);
			}
			index_offset += faceVertCount;
		}
	}

	return indices;
}

#endif