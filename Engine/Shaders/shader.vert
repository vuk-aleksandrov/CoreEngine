#version 410

layout(location=0) in vec4 vertPosition;
layout(location=1) in vec4 vertNormal;

out vec4 Color;

uniform vec3 Camera;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	vec4 normal = normalize( vec4(Camera, 1) - vertNormal );
	float x = ( normal.x+normal.y+normal.z ) / 3;
	Color = vec4(x, x, x, 1);

	gl_Position = Projection * View *(vertPosition);
}