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
    include/EngineRunnerImpl.hpp
    src/EngineRunnerImpl.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
	include//
	..//GraphicalWindow//GLFWWindow//include//
	..//GraphicalWindow//Events//include//
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} PRIVATE
    GraphicalWindow
)

add_dependencies(${PROJECT_NAME}
	GraphicalWindow
)

# Organize files into folders
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    include/EngineRunner.hpp
    src/EngineRunner.cpp
    include/EngineRunnerImpl.hpp
    src/EngineRunnerImpl.cpp
)