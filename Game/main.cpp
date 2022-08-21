#pragma once

#include <OpenGL/Buffer.h>
#include <OpenGL/Shader.h>
#include <OpenGL/VertexArray.h>

#include <Window/Window.h>

#include <iostream>
#include <cmath>

#include <Math/Math.h>

int main() {
	if (!glfwInit()) {
		printf("Failed to init glfw\n");
		return -1;
	}

	Window window(600, 600, "Game");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// Vertex Array
	gl::VertexArray vertexArray;

	// Create vertex buffer

	float vertexData[] = {
		-0.5f, -0.5f, -0.5f, 1, 0, 0,
		 0.5f, -0.5f, -0.5f, 1, 0, 0,
		 0.5f,  0.5f, -0.5f, 1, 0, 0,
		 0.5f,  0.5f, -0.5f, 1, 0, 0,
		-0.5f,  0.5f, -0.5f, 1, 0, 0,
		-0.5f, -0.5f, -0.5f, 1, 0, 0,

		-0.5f, -0.5f,  0.5f, 0, 1, 0,
		 0.5f, -0.5f,  0.5f, 0, 1, 0,
		 0.5f,  0.5f,  0.5f, 0, 1, 0,
		 0.5f,  0.5f,  0.5f, 0, 1, 0,
		-0.5f,  0.5f,  0.5f, 0, 1, 0,
		-0.5f, -0.5f,  0.5f, 0, 1, 0,

		-0.5f,  0.5f,  0.5f, 0, 0, 1,
		-0.5f,  0.5f, -0.5f, 0, 0, 1,
		-0.5f, -0.5f, -0.5f, 0, 0, 1,
		-0.5f, -0.5f, -0.5f, 0, 0, 1,
		-0.5f, -0.5f,  0.5f, 0, 0, 1,
		-0.5f,  0.5f,  0.5f, 0, 0, 1,

		 0.5f,  0.5f,  0.5f, 1, 1, 0,
		 0.5f,  0.5f, -0.5f, 1, 1, 0,
		 0.5f, -0.5f, -0.5f, 1, 1, 0,
		 0.5f, -0.5f, -0.5f, 1, 1, 0,
		 0.5f, -0.5f,  0.5f, 1, 1, 0,
		 0.5f,  0.5f,  0.5f, 1, 1, 0,

		-0.5f, -0.5f, -0.5f, 1, 0, 1,
		 0.5f, -0.5f, -0.5f, 1, 0, 1,
		 0.5f, -0.5f,  0.5f, 1, 0, 1,
		 0.5f, -0.5f,  0.5f, 1, 0, 1,
		-0.5f, -0.5f,  0.5f, 1, 0, 1,
		-0.5f, -0.5f, -0.5f, 1, 0, 1,

		-0.5f,  0.5f, -0.5f, 0, 1, 1,
		 0.5f,  0.5f, -0.5f, 0, 1, 1,
		 0.5f,  0.5f,  0.5f, 0, 1, 1,
		 0.5f,  0.5f,  0.5f, 0, 1, 1,
		-0.5f,  0.5f,  0.5f, 0, 1, 1,
		-0.5f,  0.5f, -0.5f, 0, 1, 1
	};
	gl::Buffer vertexBuffer(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	vertexArray.SetVertexAttribs(6 * sizeof(float),
		{ { 3, GL_FLOAT}, {3, GL_FLOAT } }
	);

	gl::ShaderProgram program;
	program.Attach(gl::Shader(GL_VERTEX_SHADER, "C:/Projects/CoreEngine/Engine/Shaders/shader.vert"));
	program.Attach(gl::Shader(GL_FRAGMENT_SHADER, "C:/Projects/CoreEngine/Engine/Shaders/shader.frag"));
	program.Link();
	program.Use();

	float a = 0.f, b = 0.f, c = 0.f;
	bool q = 0;
	while (window.IsOpen()) {
		// Render here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		math::mat4 rotateX = {
			1.f,    0.f,     0.f, 0.f,
			0.f, cos(a), -sin(a), 0.f,
			0.f, sin(a),  cos(a), 0.f,
			0.f,	0.f,	 0.f, 1.f
		};

		math::mat4 rotateY = {
			cos(b), 0, -sin(b), 0,
			  0   , 1,   0   , 0,
		    sin(b), 0, cos(b), 0,
			  0   , 0,   0   , 1
		};

		math::mat4 rotateZ[] = {
			cos(c), -sin(c), 0, 0,
			sin(c),  cos(c), 0, 0,
			  0   ,    0   , 1, 0,
			  0   ,    0   , 0, 1
		};

		float FOV = pi / 2.f;
		float f = 1.0f / tan(FOV / 2.f);

		float nearZ =.01f, farZ = 100.0f;
		float x = (farZ) / (farZ-nearZ);
		float y = 2.f * (farZ * nearZ) / (farZ-nearZ);

		math::mat4 projection = {
			f, 0, 0, 0,
			0, f, 0, 0,
			0, 0, x, y,
			0, 0, 0, 1
		};

		program.SetUniform_m4("rotateX", rotateX.data);
		program.SetUniform_m4("rotateY", rotateY.data);
		program.SetUniform_m4("projection", projection.data);
		a += 0.01f;
		b += 0.02f;
		c += 0.03f;
		glDrawArrays(GL_TRIANGLES, 0, 36);
		window.Update();
	}
	return 0;
}