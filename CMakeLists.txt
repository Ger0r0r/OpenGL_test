cmake_minimum_required(VERSION 3.13)

set( CMAKE_CXX_COMPILER C:/msys64/ucrt64/bin/g++.exe )
set( CMAKE_C_COMPILER C:/msys64/ucrt64/bin/gcc.exe )

set(PROJECT_NAME TestOpenGL)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)