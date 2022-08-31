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
	return pos;
}

bool Input::MouseButtonPressed(int button)
{
	return glfwGetMouseButton(glfwGetCurrentContext(), button);
}
