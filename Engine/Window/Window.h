#pragma once

#include <GLFW/glfw3.h>

#include <string>

class Window 
{
public:
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

	inline void SetTitle(std::string title) {
		glfwSetWindowTitle(handle, title.c_str());
	}
private:
	double previousTime = glfwGetTime();
	int frameCount = 0;
};