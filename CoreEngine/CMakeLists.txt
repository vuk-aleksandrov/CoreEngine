cmake_minimum_required(VERSION 3.10)

project(CoreEngine)

set(CMAKE_CXX_STANDARD 17)

add_library(CoreEngine SHARED include/CoreEngine.h src/CoreEngine.cpp)

target_include_directories(CoreEngine PUBLIC include/)

target_compile_definitions(CoreEngine PRIVATE "CORE_DLL_EXPORTS")