cmake_minimum_required(VERSION 3.24)

project(Core)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DCORE_EXPORT)

# Find and link OpenGL
find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} SHARED
	include/EngineRunner.hpp
    src/EngineRunner.cpp
)

include_directories(
	include
)

# Include directories
include_directories(
    ..//ExternalGraphicsLibs//include
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} PRIVATE
    ExternalGraphicsLibs
)

add_dependencies(${PROJECT_NAME} 
	ExternalGraphicsLibs
)