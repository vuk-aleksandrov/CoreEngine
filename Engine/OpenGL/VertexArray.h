#pragma once

#include "glad/glad.h"

#include <cstdint>

#include <initializer_list>

namespace gl
{
	struct VertexAttrib {
		uint32_t len;
		GLenum type;
		bool normalized = false;
	};

	struct VertexArray
	{
		uint32_t id;

		VertexArray();
		~VertexArray();

		void Bind();

		void SetVertexAttribs(size_t stride, std::initializer_list<VertexAttrib> vertexAttribs);
	};
}