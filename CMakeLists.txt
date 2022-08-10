cmake_minimum_required(VERSION 3.10)

project(Game)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_executable(${PROJECT_NAME} Game/src/main.cpp)

add_subdirectory(CoreEngine)
target_link_libraries(Game PUBLIC CoreEngine)
