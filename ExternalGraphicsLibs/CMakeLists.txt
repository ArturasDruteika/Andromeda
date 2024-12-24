cmake_minimum_required(VERSION 3.24.0)
project(ExternalGraphicsLibs)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

# Find and configure OpenGL
find_package(OpenGL REQUIRED)

# GLFW options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Add GLFW library
add_subdirectory(glfw)

# Create an interface library to expose GLFW and OpenGL
add_library(ExternalGraphicsLibs INTERFACE)
target_include_directories(ExternalGraphicsLibs INTERFACE
    glfw/include
)
target_link_libraries(ExternalGraphicsLibs INTERFACE
    glfw
    OpenGL::GL
)
