#version 410

in vec4 Color;

layout(location=0) out vec4 fragColor;

float near = 0.1f;
float far = 100.0f;

float linearizeDepth(float depth)
{
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

void main() 
{
	fragColor = vec4(vec3(linearizeDepth(gl_FragCoord.z)/far)+0.5, 1.0);
}