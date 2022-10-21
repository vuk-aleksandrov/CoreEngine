#include "Window.h"

#include <iostream>
#include <cstdio>
#include <cassert>


Window::Window(int width, int height, const char* title)
{
	handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
	assert(handle);

	glfwMakeContextCurrent(handle);

	
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	
	//glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
	// Show FPS
	frameCount++;
	double currentTime = glfwGetTime();
	const double elapsedTime = currentTime - previousTime;
	if (elapsedTime >= 1) {
		SetTitle("Game  FPS " + std::to_string(frameCount));
		frameCount = 0;
		previousTime = currentTime;
	}

	glfwSwapInterval(1);
	glfwSwapBuffers(handle);
	glfwPollEvents();
}

