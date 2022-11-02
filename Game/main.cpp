#pragma once

#include <OpenGL/Buffer.h>
#include <OpenGL/Shader.h>
#include <OpenGL/VertexArray.h>

#include <Window/Window.h>
#include <Input/Input.h>

#include <Math/Math.h>

#include "Mesh.h"
#include "Camera/Camera.h"

int main()
{
	if (!glfwInit()) {
		printf("Failed to init glfw\n");
		return -1;
	}

	Window window(1600, 900, "Game");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize glad\n");
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// Vertex Array
	gl::VertexArray vertexArray;

	// Create vertex buffer

	Mesh teapot("C:/Projects/CoreEngine/Engine/Models/Teapot.obj");

	gl::Buffer vertexBuffer(GL_ARRAY_BUFFER, teapot.vertexData.size() * 3 * sizeof(float), teapot.vertexData.data(), GL_STATIC_DRAW);

	vertexArray.SetVertexAttribs(6 * sizeof(float),
		{ { 3, GL_FLOAT}, { 3, GL_FLOAT} }
	);

	gl::ShaderProgram program;
	program.Attach(gl::Shader(GL_VERTEX_SHADER, "C:/Projects/CoreEngine/Engine/Shaders/shader.vert"));
	program.Attach(gl::Shader(GL_FRAGMENT_SHADER, "C:/Projects/CoreEngine/Engine/Shaders/shader.frag"));
	program.Link();
	program.Use();

	Camera camera;

	while (window.IsOpen() && !Input::KeyPressed(KEY_Q))
	{
		// Render here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Update();

		program.SetUniform_m4("View", &camera.inverseViewMat[0].x);
		program.SetUniform_m4("Projection", &camera.perspectiveMat[0].x);
		program.SetUniform_v4("Camera", &camera.position[0]);

		glDrawArrays(GL_TRIANGLES, 0, teapot.vertexData.size() / 2);

		window.Update();
	}

	return 0;
}