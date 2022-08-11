#pragma once

#include "glad/glad.h"

#include <cstdint>

namespace gl 
{
	struct Buffer
	{
		uint32_t id;
		GLenum target;
		size_t size;
		void* data;
		
		Buffer(GLenum target, size_t size, void* data, 
			GLenum usage=GL_STATIC_DRAW);
		~Buffer();

		void Bind();
	};
}