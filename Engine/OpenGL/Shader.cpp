#include "Shader.h"

#include <fstream>

namespace gl
{

	Shader::Shader(GLenum type, const char* srcDest)
	{
		id = glCreateShader(type);

		std::string src = LoadFile(srcDest);
		const char* src_cc[] = { src.c_str() };

		glShaderSource(id, 1, src_cc, nullptr);
		glCompileShader(id);
		LogCompileStatus();
	}

	Shader::~Shader()
	{
		Delete();
	}

	void Shader::Delete()
	{
		glDeleteShader(id);
	}

	std::string Shader::LoadFile(const char* fileName)
	{
		std::ifstream file(fileName);
		std::string line;

		std::string strFile;
		while (getline(file, line))
			strFile += line + '\n';
		
		return strFile;
	}

	void Shader::LogCompileStatus()
	{
		GLint result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (GL_FALSE == result)
		{
			fprintf(stderr, "Vertex shader compilation failed!\n");
			GLint logLen;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);
			if (logLen > 0)
			{
				char* log = (char*)malloc(logLen);
				GLsizei written;
				glGetShaderInfoLog(id, logLen, &written, log);
				fprintf(stderr, "Shader log:\n%s", log);
				free(log);
			}

			printf("Shader compilation failed\n");
		}
	}

	ShaderProgram::ShaderProgram()
	{
		id = glCreateProgram();
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(id);
	}

	void ShaderProgram::Attach(Shader& shader)
	{
		glAttachShader(id, shader.id);
		shader.Delete();
	}

	void ShaderProgram::Link()
	{
		glLinkProgram(id);
		LogLinkStatus();
	}

	void ShaderProgram::LogLinkStatus()
	{
		GLint status;
		glGetProgramiv(id, GL_LINK_STATUS, &status);
		if (GL_FALSE == status) {
			fprintf(stderr, "Failed to link shader program!\n");
			GLint logLen;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLen);
			if (logLen > 0)
			{
				char* log = (char*)malloc(logLen);
				GLsizei written;
				glGetProgramInfoLog(id, logLen, &written, log);
				fprintf(stderr, "Program log: \n%s", log);
				free(log);
			}
		}
	}

	void ShaderProgram::Use()
	{
		glUseProgram(id);
	}
}