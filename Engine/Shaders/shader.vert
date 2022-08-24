#version 410

layout(location=0) in vec4 vertPosition;
layout(location=1) in vec3 vertColor;

out vec3 Color;

uniform mat4 Rotation;
uniform mat4 Projection;

void main()
{
	Color=vertColor;

	gl_Position= Projection * Rotation * vertPosition;
}