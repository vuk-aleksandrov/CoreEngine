#pragma once

#include <GLFW/glfw3.h>

struct Window 
{
	GLFWwindow* handle;

	Window(int width, int height, const char* title);
	~Window();

	bool IsOpen();

	void Update();

	inline int Width() {
		int width;
		glfwGetWindowSize(handle, &width, nullptr);
		return width;
	}

	inline int Height() {
		int height;
		glfwGetWindowSize(handle, nullptr, &height);
		return height;
	}
};