cmake_minimum_required(VERSION 3.24.0)
project(ExternalGraphicsLibs)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif ()

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Add the GLFW library
add_subdirectory(glfw)