#pragma once

#include "Mesh.h"

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

Mesh::Mesh(const char* fileDir)
{
	vertices.reserve(600);
	normals.reserve(600);

	vertexData.reserve(120'000);

	FILE* file = fopen(fileDir, "r");
	if (file == NULL) {
		std::cout << "file " << fileDir << " not found\n";
		return;
	}

	char line[128];

	while (fgets(line, 128, file)) {
		if (line[0] == 'v') 
		{
			if(line[1]=='t') continue;

			int i = 2;
			if (line[1] == 'n')
				i = 3;

			const char* num = &line[i];
			math::vec3 v;
			int j = 0;
			while (line[i] != '\0') 
			{
				if (line[i] == ' ' || line[i] == '\n') 
				{
					line[i] = '\0';
					v[j++] = std::stof(num);
					num = &line[++i];
				}
				else i++;
			}
			if (line[1] == 'n') 
				normals.push_back(v);
			else 
				vertices.push_back(v);
		}
		else if (line[0] == 'f') 
		{
			int i = 2;
			const char* num = &line[i];
			
			int c = 0;
			while (line[i] != '\0') 
			{
				if (line[i] == '/') 
				{
					line[i] = '\0';
					int index = std::stoi(num) - 1;
					c++;
					if (c == 1) {
						vertexData.push_back(vertices[index]);
					}
					else if (c == 2) {
						vertexData.push_back(normals[index]);
					}
					num = &line[i + 1];
				}
				else if (line[i] == ' ' || line[i] == '\n') 
				{
					// This one should be for texture coordinates
					num = &line[i + 1];
					c = 0;
				}

				i++;
			}
		}
	}


	fclose(file);
}

Mesh::~Mesh()
{

}
