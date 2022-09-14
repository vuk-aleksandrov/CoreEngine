#pragma once

#include <OpenGL/Buffer.h>
#include <OpenGL/Shader.h>
#include <OpenGL/VertexArray.h>

#include <Window/Window.h>
#include <Input/Input.h>

#include <Math/Math.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include "Mesh.h"

math::mat4 MakeViewMatrix(math::vec3 a, math::vec3 b, math::vec3 c, math::vec3 t)
{
	return {
		a.x, b.x, c.x, 0,
		a.y, b.y, c.y, 0,
		a.z, b.z, c.z, 0,
		-math::Dot(t, a), 
		-math::Dot(t, b), 
		-math::Dot(t, c), 1
	};
}

int main() 
{
	if (!glfwInit()) {
		printf("Failed to init glfw\n");
		return -1;
	}
	
	Window window(800, 450, "Game");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize glad\n");
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// Vertex Array
	gl::VertexArray vertexArray;

	// Create vertex buffer

	Mesh teapot("C:/Projects/CoreEngine/Engine/Models/Teapot.obj");

	gl::Buffer vertexBuffer(GL_ARRAY_BUFFER, teapot.vertexData.size()*3*sizeof(float), teapot.vertexData.data(), GL_STATIC_DRAW);

	vertexArray.SetVertexAttribs(6 * sizeof(float),
		{ { 3, GL_FLOAT}, { 3, GL_FLOAT} }
	);

	gl::ShaderProgram program;
	program.Attach(gl::Shader(GL_VERTEX_SHADER, "C:/Projects/CoreEngine/Engine/Shaders/shader.vert"));
	program.Attach(gl::Shader(GL_FRAGMENT_SHADER, "C:/Projects/CoreEngine/Engine/Shaders/shader.frag"));
	program.Link();
	program.Use();

	// Perspective  matrix

	math::mat4 projection;
	float aspectRatio = (float)window.Height() / window.Width();
	float zNear = 0.1f, zFar = 1000.0f;
	math::Perspective(projection, (float)pi_quarter, aspectRatio, zNear, zFar);

	// Camera position
	math::vec3 cameraPos;
	cameraPos.z = 0;

	while (window.IsOpen())
	{
		// Render here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (Input::KeyPressed(KEY_LEFT))
			cameraPos.x += .5f;
		if (Input::KeyPressed(KEY_RIGHT))
			cameraPos.x -= .5f;
		if (Input::KeyPressed(KEY_DOWN))
			cameraPos.y += .5f;
		if (Input::KeyPressed(KEY_UP))
			cameraPos.y -= .5f;
		if (Input::KeyPressed(KEY_S))
			cameraPos.z += .5f;
		if (Input::KeyPressed(KEY_W))
			cameraPos.z -= .5f;

		/* Camera System */

		// Calculate forward, right and up direction
		math::vec2 mousePos = Input::MousePosition();

		math::vec4 forward4 = { 0, 0, -1 , 1};
		math::mat4 xrot;
		math::xRotation(pi_quarter, xrot);
		math::Mul(xrot, forward4, forward4);
		math::vec3 forward = { forward4.x, forward4.y, forward4.z };

		math::vec3 right = {forward.z, 0.0f, -forward.x};
		auto rightLen = math::Length(right);
		right.x /= rightLen; right.z /= rightLen;

		math::vec3 up;
		math::Cross(forward, right, up);
		
		// Create inverse view matrix
		
		math::mat4 view = MakeViewMatrix(right, up, forward, cameraPos);

		program.SetUniform_m4("View", &view[0].x);
		program.SetUniform_m4("Projection", &projection[0].x);
		program.SetUniform_v3("Camera", &cameraPos[0]);

		glDrawArrays(GL_TRIANGLES, 0, teapot.vertexData.size()/2);

		window.Update();
	}

	return 0;
}