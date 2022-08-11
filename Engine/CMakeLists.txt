cmake_minimum_required(VERSION 3.10)

project(Engine)

set(OPENGL_SOURCES
    OpenGL/glad/glad.h
    OpenGL/glad/glad.c
    OpenGL/glad/khrplatform.h
)

add_library(Engine OpenGL/glad/glad.c)

target_include_directories(Engine PUBLIC /)

add_subdirectory(ThirdParty/glfw)
target_link_libraries(Engine PUBLIC glfw)