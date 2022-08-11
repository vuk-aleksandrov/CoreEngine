#include "Window.h"

#include <cstdio>

Window::Window(int width, int height, const char* title)
{
	handle = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (!handle)
	{
		glfwTerminate();
		printf("Window creation error\n");
		return;
	}

	glfwMakeContextCurrent(handle);
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

