#version 410

layout(location=0) in vec2 vertPosition;
layout(location=1) in vec3 vertColor;

uniform float angle;

out vec3 Color;

void main()
{
	Color=vertColor;

	gl_Position=vec4(vertPosition.x, vertPosition.y+angle, 0.0, 1.0);
}