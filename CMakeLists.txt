cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME TestOpenGL)

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX C)

add_link_options(-static -static-libgcc -static-libstdc++)

include_directories(external/glm)
include_directories(headers)

file(GLOB CPPS "src/*.cpp")

add_executable(${PROJECT_NAME} ${CPPS})
target_link_libraries(${PROJECT_NAME} m)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)