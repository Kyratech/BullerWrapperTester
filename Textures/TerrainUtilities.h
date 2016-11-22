#ifndef TERRAIN_UTILITIES
#define TERRAIN_UTILITIES

#include <math.h>

#include <vector>

/*
 *Produces a bowl-like shape based on a hemisphere
 */
static std::vector<int> getBowlTerrainArray(int width, int height, int depth)
{
	std::vector<int> terrain(width*height, 0);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int adjacentI = std::abs(width / 2 - i);
			int squaredDepthI = adjacentI * adjacentI + depth * depth;

			int adjacentJ = std::abs(height / 2 - j);
			int squaredDepthJ = adjacentJ * adjacentJ + depth * depth;

			terrain[i + j * width] = (int) std::sqrt(std::fmin(squaredDepthI, squaredDepthJ)) * -1;
		}
	}

	return terrain;
}

#endif