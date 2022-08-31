#include "Window.h"

#include <cstdio>
#include <cassert>


Window::Window(int width, int height, const char* title)
{
	handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
	assert(handle);

	glfwMakeContextCurrent(handle);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::IsOpen()
{
	return !glfwWindowShouldClose(handle);
}

void Window::Update()
{
	glfwSwapBuffers(handle);
	glfwPollEvents();
}

