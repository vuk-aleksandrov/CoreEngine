#pragma once

#include "Camera.h"

#include <Window/Window.h>
#include <Input/Input.h>

Camera::Camera()
{
	// Initialize perspective matrix
	const float aspectRatio = (float)Window::currentWindow->Height() / Window::currentWindow->Width();
	const float zNear = 0.1f, zFar = 1000.0f;
	math::Perspective(perspectiveMat, (float)PI_QUARTER, aspectRatio, zNear, zFar);
}

void Camera::Update()
{
	math::vec2 deltaMousePos;
	math::vec2 currentMousePos = Input::MousePosition();

	math::Sub(currentMousePos, lastMousePos, deltaMousePos);
	lastMousePos = currentMousePos;

	pitch += (float)deltaMousePos.y;
	yaw += (float)deltaMousePos.x;

	pitch = std::min(pitch, (float)PI_HALF);
	pitch = std::max(pitch, (float)-PI_HALF);

	direction = { 0, 0, 1 };
	math::RotateAroundX(direction, -pitch);
	math::RotateAroundY(direction, yaw);

	math::vec3 right = { 1, 0, 0 };
	math::RotateAroundX(right, -pitch);
	math::RotateAroundY(right, yaw);

	math::vec3 up;
	math::Cross(direction, right, up);

	if (Input::KeyPressed(KEY_A))
	{
		math::vec3 v;
		math::Mul(right, 0.7f, v);
		math::Sub(position, v, position);
	}
	if (Input::KeyPressed(KEY_D))
	{
		math::vec3 v;
		math::Mul(right, 0.7f, v);
		math::Add(position, v, position);
	}
	if (Input::KeyPressed(KEY_W))
	{
		math::vec3 v;
		math::Mul(direction, 0.7f, v);
		math::Sub(position, v, position);
	}
	if (Input::KeyPressed(KEY_S))
	{
		math::vec3 v;
		math::Mul(direction, 0.7f, v);
		math::Add(position, v, position);
	}

	inverseViewMat = InverseView(right, up, direction, position);
}