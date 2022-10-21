#pragma once

#include "Mesh.h"

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cassert>

Mesh::Mesh(const char* fileDir)
{
	vertexPool[0].reserve(600);
	vertexPool[1].reserve(600);
	vertexData.reserve(100'000);

	FILE* file = fopen(fileDir, "r");
	assert(file);

	char s[20];
	while (fscanf(file, "%s", s) != EOF)
	{
		if (s[0] == 'v' && s[1] != 't')
		{
			math::vec3 v;
			fscanf(file, "%f %f %f", &v.x, &v.y, &v.z);

			if (!strcmp(s, "v"))
				vertexPool[0].push_back(v);
			else if (!strcmp(s, "vn"))
				vertexPool[1].push_back(v);
		}
		else if (s[0] == 'f')
		{
			int n = 3;
			while (n--)
			{
				fscanf(file, "%s", s);

				int i = 0;
				int index = 0;
				int c = 0;
				while (s[i] != '\0')
				{
					if (s[i] == '/' && c < 2)
					{
						vertexData.push_back(vertexPool[c++][index - 1]);
						index = 0;
					}
					else
						index = index * 10 + s[i] - '0';

					i++;
				}
				// vertexData.push_back(vertexPool[1][index - 1]);
			}
		}
	}

	fclose(file);
}