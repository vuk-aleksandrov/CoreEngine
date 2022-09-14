#pragma once

#include <vector>

#include <Math/Math.h>

struct Mesh
{
	// first vector contains vertices and second normals
	std::vector<math::vec3> vertexPool[2];

	std::vector<math::vec3> vertexData;
	
	Mesh(const char* fileDir);
};