#pragma once

#include <GLFW/glfw3.h>

struct Window 
{
	GLFWwindow* handle;

	Window(int width, int height, const char* title);
	~Window();

	bool IsOpen();

	void Update();
};