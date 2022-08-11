#pragma once

#include "glad/glad.h"

#include <cstdint>
#include <string>

namespace gl
{
	class Shader {
	public:
		uint32_t id;
		Shader(GLenum type, const char* srcDest);
		~Shader();

		void Delete();
	private:
		std::string LoadFile(const char* fileName);

		void LogCompileStatus();
	};

	class ShaderProgram
	{
	public:
		uint32_t id;
		ShaderProgram();
		~ShaderProgram();
		void Attach(Shader& shader);

		void Link();

		void Use();
	private:
		void LogLinkStatus();
	};
}