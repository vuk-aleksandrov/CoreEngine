#pragma once

#include <OpenGL/Buffer.h>
#include <OpenGL/Shader.h>
#include <OpenGL/VertexArray.h>

#include <Window/Window.h>

#include <iostream>
#include <cmath>

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

	// Vertex Array
	gl::VertexArray vertexArray;

	// Create vertex buffer
	float vertexData[] = {
	//	   vertices						colors
		 -0.5f, -0.5f,				1.0f, 0.0f, 0.0f,
		  0.5f,	-0.5f,				0.0f, 1.0f, 0.0f,
		  0.0f,	 0.5f,				0.0f, 0.0f, 1.0f,
	};
	gl::Buffer vertexBuffer(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	vertexArray.SetVertexAttribs(5 * sizeof(float),
		{ {2, GL_FLOAT},{3, GL_FLOAT} });

	// Create index buffer
	uint32_t indices[] = {
		0, 1, 2
	};

	gl::Buffer indexBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	gl::ShaderProgram program;
	program.Attach(gl::Shader(GL_VERTEX_SHADER, "C:/Projects/CoreEngine/Engine/Shaders/shader.vert"));
	program.Attach(gl::Shader(GL_FRAGMENT_SHADER, "C:/Projects/CoreEngine/Engine/Shaders/shader.frag"));
	program.Link();
	program.Use();

	float angle = 0.0f;
	while (window.IsOpen()) {
		// Render here
		glClear(GL_COLOR_BUFFER_BIT);
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		program.SetUniform_f("angle", angle);
		angle += 0.01;

		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);

		window.Update();
	}
	return 0;
}