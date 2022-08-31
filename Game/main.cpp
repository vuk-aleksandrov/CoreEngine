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

int main() {
	assert(glfwInit());

	Window window(800, 450, "Game");

	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

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
	math::Perspective(projection, (float)pi_half / 2, aspectRatio, 0.1f, 1000.0f);

	// Rotation angle
	float theta = 0.f;

	// Camera position
	math::vec4 camera;
	camera.z = 40;

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

		if (Input::KeyPressed(KEY_LEFT))
			camera.x += 0.05f;
		if (Input::KeyPressed(KEY_RIGHT))
			camera.x -= 0.05f;
		if (Input::KeyPressed(KEY_DOWN))
			camera.y += 0.05f;
		if (Input::KeyPressed(KEY_UP))
			camera.y -= 0.05f;
		if (Input::KeyPressed(KEY_S))
			camera.z += 0.05f;
		if (Input::KeyPressed(KEY_W))
			camera.z -= 0.05f;

		program.SetUniform_v4("Camera", &camera[0]);
		program.SetUniform_m4("Rotation", &rotation[0].x);
		program.SetUniform_m4("Projection", &projection[0].x);

		theta += 0.01f;

		glDrawArrays(GL_TRIANGLES, 0, teapot.vertexData.size()/2);

		window.Update();
	}

	return 0;
}