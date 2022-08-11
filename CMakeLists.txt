cmake_minimum_required(VERSION 3.10)

project(Game)

add_executable(Game Game/main.cpp)

add_subdirectory(Engine)
target_link_libraries(Game PUBLIC Engine)