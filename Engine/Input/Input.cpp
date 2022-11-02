#include "Input.h"

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
	
	// Map to range -1 -> +1
	return { pos.x * 2.0 / (double)width - 1.0f, 1.0 - pos.y * 2.0 / (double)height };
}

bool Input::MouseButtonPressed(int button)
{
	return glfwGetMouseButton(glfwGetCurrentContext(), button);
}
