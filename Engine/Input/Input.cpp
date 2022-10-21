#include "Input.h"

#include <GLFW/glfw3.h>

bool Input::KeyPressed(int key)
{
	return glfwGetKey(glfwGetCurrentContext(), key);
}

math::vec2 Input::MousePosition()
{
	math::vec2 pos;
	glfwGetCursorPos(glfwGetCurrentContext(), &pos.x, &pos.y);
	
	int width, height;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
	
	//return { ((pos.x * 2 / (double)width) - 1.0, 1.0 - (pos.y * 2 / (double)height)) };

	return pos;
}

bool Input::MouseButtonPressed(int button)
{
	return glfwGetMouseButton(glfwGetCurrentContext(), button);
}
