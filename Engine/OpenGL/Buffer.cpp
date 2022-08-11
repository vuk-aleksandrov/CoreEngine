#include "Buffer.h"

namespace gl {

	Buffer::Buffer(GLenum target, size_t size, void* data, GLenum usage)
		:target(target), size(size), data(data)
	{
		glGenBuffers(1, &id);
		glBindBuffer(target, id);
		glBufferData(target, size, data, usage);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &id);
	}

	void Buffer::Bind()
	{
		glBindBuffer(target, id);
	}
}