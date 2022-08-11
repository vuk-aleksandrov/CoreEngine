#include "VertexArray.h"

namespace gl
{

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &id);
		glBindVertexArray(id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(id);
	}

	void VertexArray::SetVertexAttribs(size_t stride, std::initializer_list<VertexAttrib> vertexAttribs)
	{
		int index = 0;
		size_t offset = 0;
		for (const VertexAttrib& attrib:vertexAttribs)
		{	
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, attrib.len, attrib.type,
				attrib.normalized, stride, (const void*)(offset));

			index++;

			size_t typeSize = sizeof(GLfloat);
			if (attrib.type <= GL_UNSIGNED_BYTE)
				typeSize = sizeof(GLbyte);
			else if (attrib.type <= GL_UNSIGNED_SHORT)
				typeSize = sizeof(GLshort);

			offset += attrib.len * typeSize;
		}
	}

}