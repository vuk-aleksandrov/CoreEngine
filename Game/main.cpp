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
#include <cstdlib>
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

namespace math
{
	inline void Sub(const math::vec2& v1, const math::vec2& v2, math::vec2& dest)
	{
		dest = { v1.x - v2.x, v1.y - v2.y };
	}
}

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

	// Perspective  matrix
	math::mat4 projection;
	float aspectRatio = (float)window.Height() / window.Width();
	float zNear = 0.1f, zFar = 1000.0f;
	math::Perspective(projection, (float)pi_quarter, aspectRatio, zNear, zFar);
	//math::Perspective2(projection, -0.5f, 0.5f, -0.5, 0.5f, zNear, zFar);

	// Camera position
	math::vec3 cameraPos;

	math::vec2 lastMousePos = { 0, 0 };
	float pitch = 0;
	float yaw = 0;
	while (window.IsOpen() && !Input::KeyPressed(KEY_Q))
	{
		// Render here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Camera System */


		math::vec2 mousePos;
		math::vec2 currentMousePos = Input::MousePosition();
		currentMousePos = { currentMousePos.x * 2 / window.Width() - 1, 1.0 - currentMousePos.y * 2 / window.Height() };
		//std::cout << currentMousePos.x << ' ' << currentMousePos.y << std::endl;

		math::Sub(currentMousePos, lastMousePos, mousePos);
		lastMousePos = currentMousePos;

		pitch += mousePos.y;
		yaw += mousePos.x;

		/*if (pitch >= pi_half)
			pitch = pi_half;
		if (pitch <= -pi_half) pitch = -pi_half;
		std::cout << pitch << ' ' << yaw << std::endl;
		*/

		math::vec3 forward = { 0, 0, 1 };
		math::vec3 right = { 1, 0, 0 };
		math::vec3 up = { 0, 1, 0 };

		//Normalize(forward);

		math::RotateAroundX(forward, pitch);
		math::RotateAroundY(forward, -yaw);

		math::RotateAroundX(right, pitch);
		math::RotateAroundY(right, -yaw);

		math::RotateAroundX(up, pitch);
		math::RotateAroundY(up, -yaw);

// 		math::vec3 forward = {
// 			-cos(yaw) * cos(pitch),
// 			sin(pitch),
// 			sin(yaw) * cos(pitch)
// 		};
// 
// 		//math::vec3 forward = { 0, 1, 0 };
// 		math::vec3 right;
// 		math::Cross({ 0, 1, 0 }, forward, right);
// 		Normalize(right);
// 
// 		math::vec3 up;
// 		math::Cross(forward, right, up);
// 		Normalize(up);

		if (Input::KeyPressed(KEY_A))
		{
			math::vec3 v;
			math::Mul(right, 0.7f, v);
			math::Sub(cameraPos, v, cameraPos);
		}
		if (Input::KeyPressed(KEY_D))
		{
			math::vec3 v;
			math::Mul(right, 0.7f, v);
			math::Add(cameraPos, v, cameraPos);
		}
		if (Input::KeyPressed(KEY_W))
		{
			math::vec3 v;
			math::Mul(forward, 0.7f, v);
			math::Add(cameraPos, v, cameraPos);
		}
		if (Input::KeyPressed(KEY_S))
		{
			math::vec3 v;
			math::Mul(forward, 0.7f, v);
			math::Sub(cameraPos, v, cameraPos);
		}

		// Create inverse view matrix

		math::mat4 view = MakeViewMatrix(right, up, forward, cameraPos);

		program.SetUniform_m4("View", &view[0].x);
		program.SetUniform_m4("Projection", &projection[0].x);
		program.SetUniform_v4("Camera", &cameraPos[0]);

		glDrawArrays(GL_TRIANGLES, 0, teapot.vertexData.size() / 2);

		window.Update();
	}

	return 0;
}