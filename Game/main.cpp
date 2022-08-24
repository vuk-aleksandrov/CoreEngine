#pragma once

#include <OpenGL/Buffer.h>
#include <OpenGL/Shader.h>
#include <OpenGL/VertexArray.h>

#include <Window/Window.h>

#include <Math/Math.h>

#include <iostream>

int main() {
	if (!glfwInit()) {
		printf("Failed to init glfw\n");
		return -1;
	}

	Window window(800, 450, "Game");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// Vertex Array
	gl::VertexArray vertexArray;

	// Create vertex buffer

	float vertexData[] = {
		//	  vertex positions	   vertex colors
			-0.5f, -0.5f, -0.5f,	 1, 0, 0,
			 0.5f, -0.5f, -0.5f,	 1, 0, 0,
			 0.5f,  0.5f, -0.5f,	 1, 0, 0,
			 0.5f,  0.5f, -0.5f,	 1, 0, 0,
			-0.5f,  0.5f, -0.5f,	 1, 0, 0,
			-0.5f, -0.5f, -0.5f,	 1, 0, 0,

			-0.5f, -0.5f,  0.5f,	 0, 1, 0,
			 0.5f, -0.5f,  0.5f,	 0, 1, 0,
			 0.5f,  0.5f,  0.5f,	 0, 1, 0,
			 0.5f,  0.5f,  0.5f,	 0, 1, 0,
			-0.5f,  0.5f,  0.5f,	 0, 1, 0,
			-0.5f, -0.5f,  0.5f,	 0, 1, 0,

			-0.5f,  0.5f,  0.5f,	 0, 0, 1,
			-0.5f,  0.5f, -0.5f,	 0, 0, 1,
			-0.5f, -0.5f, -0.5f,	 0, 0, 1,
			-0.5f, -0.5f, -0.5f,	 0, 0, 1,
			-0.5f, -0.5f,  0.5f,	 0, 0, 1,
			-0.5f,  0.5f,  0.5f,	 0, 0, 1,

			 0.5f,  0.5f,  0.5f,	 1, 1, 0,
			 0.5f,  0.5f, -0.5f,	 1, 1, 0,
			 0.5f, -0.5f, -0.5f,	 1, 1, 0,
			 0.5f, -0.5f, -0.5f,	 1, 1, 0,
			 0.5f, -0.5f,  0.5f,	 1, 1, 0,
			 0.5f,  0.5f,  0.5f,	 1, 1, 0,

			-0.5f, -0.5f, -0.5f,	 1, 0, 1,
			 0.5f, -0.5f, -0.5f,	 1, 0, 1,
			 0.5f, -0.5f,  0.5f,	 1, 0, 1,
			 0.5f, -0.5f,  0.5f,	 1, 0, 1,
			-0.5f, -0.5f,  0.5f,	 1, 0, 1,
			-0.5f, -0.5f, -0.5f,	 1, 0, 1,

			-0.5f,  0.5f, -0.5f,	 0, 1, 1,
			 0.5f,  0.5f, -0.5f,	 0, 1, 1,
			 0.5f,  0.5f,  0.5f,	 0, 1, 1,
			 0.5f,  0.5f,  0.5f,	 0, 1, 1,
			-0.5f,  0.5f,  0.5f,	 0, 1, 1,
			-0.5f,  0.5f, -0.5f,	 0, 1, 1
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

	// Perspective  matrix
	math::mat4 projection;
	math::Perspective(projection, (float)pi_half, (float)9 / 16, 0.1f, 1000.0f);

	float theta = 0.f;

	while (window.IsOpen())
	{
		// Render here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		math::mat4 xrotation;
		math::xRotation(theta, xrotation);

		math::mat4 yrotation;
		math::yRotation(theta, yrotation);

		math::mat4 rotation;
		math::Mul(xrotation, yrotation, rotation);

		program.SetUniform_m4("Rotation", &rotation[0].x);
		program.SetUniform_m4("Projection", &projection[0].x);

		theta += 0.01f;

		glDrawArrays(GL_TRIANGLES, 0, 36);

		window.Update();
	}

	return 0;
}