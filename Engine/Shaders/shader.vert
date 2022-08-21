#version 410

layout(location=0) in vec4 vertPosition;
layout(location=1) in vec3 vertColor;

out vec3 Color;

uniform mat4 rotateX;
uniform mat4 rotateY;
uniform mat4 projection;

void main()
{
	Color=vertColor;

	gl_Position=vec4(projection*rotateX*rotateY*vertPosition);
}