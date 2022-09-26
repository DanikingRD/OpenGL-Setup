cmake_minimum_required(VERSION 3.8)

project(OpenGLSetup)
# C++ 14 required
set(CMAKE_CXX_STANDARD 14)
# External Dependencies
set(GLFW_SOURCE_DIR "external/glfw")
set(GLEW_SOURCE_DIR "external/glew")

add_subdirectory(${GLFW_SOURCE_DIR})
add_subdirectory(${GLEW_SOURCE_DIR})
# Header files
include_directories(
    ${GLFW_SOURCE_DIR}/include
    ${GLEW_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME} src/main.cpp)

# Link against dependencies
target_link_libraries(${PROJECT_NAME} glfw libglew_static)