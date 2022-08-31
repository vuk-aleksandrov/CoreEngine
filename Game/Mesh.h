#pragma once

#include <vector>

#include <Math/Math.h>

class Mesh
{
public:
	Mesh(const char* fileDir);
	~Mesh();

	std::vector<math::vec3> vertices, normals;
	std::vector<math::vec3> vertexData;
};