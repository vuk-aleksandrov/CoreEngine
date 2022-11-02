#pragma once

#include <Math/Math.h>

struct Camera
{
	math::vec3 position;
	math::vec3 direction = { 0, 0, 1 };

	math::mat4 perspectiveMat;
	math::mat4 inverseViewMat;

	float pitch = 0, yaw = 0;
	math::vec2 lastMousePos;

	Camera();

	void Update();
};
