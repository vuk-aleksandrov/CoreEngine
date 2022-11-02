cmake_minimum_required(VERSION 3.10)

project(Engine)

add_library(Engine 
	"Math/Math.h"
	"OpenGL/glad/glad.h"
	"OpenGL/glad/glad.c"
	"OpenGL/Buffer.h"
	"OpenGL/Buffer.cpp"
	"OpenGL/Shader.h"
	"OpenGL/Shader.cpp"
	"OpenGL/VertexArray.h"
	"OpenGL/VertexArray.cpp"
	"Window/Window.cpp"
	"Window/Window.h"
	"Input/Input.h"
	"Input/Input.cpp"
	"Camera/Camera.h"
	"Camera/Camera.cpp"
 )
target_include_directories(Engine PUBLIC /)

add_subdirectory(ThirdParty/glfw)
target_link_libraries(Engine PUBLIC glfw)