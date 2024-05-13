cmake_minimum_required(VERSION 3.13)

set( CMAKE_CXX_COMPILER C:/msys64/ucrt64/bin/g++.exe )
set( CMAKE_C_COMPILER C:/msys64/ucrt64/bin/gcc.exe )

project(glad)

add_library(glad STATIC include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)