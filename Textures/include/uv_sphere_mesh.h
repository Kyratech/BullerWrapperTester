#ifndef UV_SPHERE_H
#define UV_SPHERE_H

#include "Tester.h"
#include <iostream>

/*  Produce the vertex data for a sphere with smooth shading.
    The normal at each vertex is along the direction from the centre to the vertex.
    Segments = number of bands of quads split by lines of longitude
    Rings = number of bands of quads split by the lines of latitude
    There are (rings + 1) lines of latitude, inc the points at the top and bottom
    No generated UVs. Sorry.
*/
static std::vector<struct Vertex> GetSphereVertices(int segments, int rings, double radius)
{
    /* Minimum of 3 segments and 3 rings */
    if(segments < 3) segments = 3;
    if(rings < 3) rings = 3;

    std::vector<struct Vertex> vertices;

    double ringAngle = 180.0f / rings;
    double segmentAngle = 360.0f / segments;

    /*
     * NB: rn is the nth line of latitude, starting at the top
     * bn is the nth line of longitude, starting from positive X direction
     * This notation is to save space; the parameters still define the number of
     * quad bands in the respective direction, NOT the lines of lat/long
     */

    //Oth line of latitude is the point on top
    struct Vertex r0 = {{0.0, radius, 0.0},   {0.0f, 1.0f, 0.0f}};
    vertices.push_back(r0);

    //1th to nth lines of latitude
    for(int j = 1; j < rings; j++)
    {
        double thetaj = glm::radians(90 - (j * ringAngle)); //theta(j)
        for(int i = 0; i < segments; i++)
        {
            double phii = glm::radians(i * segmentAngle); //phi(i)

            double rjbiX = radius * cos(thetaj) * cos(phii);
            double rjbiY = radius * sin(thetaj);
            double rjbiZ = radius * cos(thetaj) * sin(phii);
            glm::vec3 normalrjbi = glm::normalize(glm::vec3(rjbiX, rjbiY, rjbiZ));
            struct Vertex rjbi = {{rjbiX, rjbiY, rjbiZ},    {normalrjbi.x, normalrjbi.y, normalrjbi.z}};;

            vertices.push_back(rjbi);
        }
    }

    //(rings + 1)th line of latitude is the point on bottom
    struct Vertex rn2 = {{0.0, -radius, 0.0},   {0.0f, -1.0f, 0.0f}};
    vertices.push_back(rn2);

    return vertices;
}

static std::vector<GLuint> GetSphereIndices(int segments, int rings)
{
	/* Minimum of 3 segments and 3 rings */
	if (segments < 3) segments = 3;
	if (rings < 3) rings = 3;

	std::vector<GLuint> indices;

	double ringAngle = 180.0f / rings;
	double segmentAngle = 360.0f / segments;

	/*
	* NB: rn is the nth line of latitude, starting at the top
	* bn is the nth line of longitude, starting from positive X direction
	* This notation is to save space; the parameters still define the number of
	* quad bands in the respective direction, NOT the lines of lat/long
	*/

	//Oth line of latitude is the point on top
	int i;
	double theta = glm::radians(90.0 - ringAngle);
	for (i = 0; i < segments; i++)
	{
		GLuint r1bi = 1 + i;
		GLuint r1bi2 = 1 + (i + 1) % segments;

		indices.push_back(0);
		indices.push_back(r1bi);
		indices.push_back(r1bi2);
	}

	//Middle rings are made from quads (kinda...), so require different attention
	for (int j = 1; j < rings - 1; j++)
	{
		double thetaj = glm::radians(90 - (j * ringAngle)); //theta(j)
		double thetaj2 = glm::radians(90 - ((j + 1) * ringAngle)); //theta(j+1)
		for (i = 0; i < segments; i++)
		{
			GLuint rjbi = 1 + ((j - 1) * segments) + i;
			GLuint rjbi2 = 1 + ((j - 1) * segments) + (i + 1) % segments;
			GLuint rj2bi = 1 + (j * segments) + i;
			GLuint rj2bi2 = 1 + (j * segments) + (i + 1) % segments;

			indices.push_back(rjbi);
			indices.push_back(rjbi2);
			indices.push_back(rj2bi);

			indices.push_back(rjbi2);
			indices.push_back(rj2bi2);
			indices.push_back(rj2bi);

			//std::cout << "r" << j << "b" << i << ":(" << rjbiX << ","  << rjbiY << "," << rjbiZ << ")" << std::endl;
			//Oh god, this is more code than I had hoped
			//Yeah, but I am particularly verbose
		}
	}

	//(rings + 1)th line of latitude is the point on bottom
	theta = glm::radians(ringAngle - 90);
	for (i = 0; i < segments; i++)
	{
		GLuint rnbi = 1 + ((rings - 2) * segments) + i;
		GLuint rnbi2 = 1 + ((rings - 2) * segments) + (i + 1) % segments;
		GLuint rn2 = 1 + ((rings - 1) * segments);


		indices.push_back(rn2);
		indices.push_back(rnbi);
		indices.push_back(rnbi2);
	}

	return indices;
}

#endif // UV_SPHERE_H
