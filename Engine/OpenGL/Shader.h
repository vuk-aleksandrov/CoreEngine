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
		std::string LoadFile(const char* fileDir);

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

		void SetUniform_i(const char* name, const int& val);
		void SetUniform_f(const char* name, const int& val);
		void SetUniform_v2(const char* name, const float* val);
		void SetUniform_v3(const char* name, const float* val);
		void SetUniform_v4(const char* name, const float* val);
		void SetUniform_m2(const char* name, const float* val, bool transpose = false);
		void SetUniform_m3(const char* name, const float* val, bool transpose = false);
		void SetUniform_m4(const char* name, const float* val, bool transpose = false);
	private:
		void LogLinkStatus();
	};
}