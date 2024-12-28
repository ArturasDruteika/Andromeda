cmake_minimum_required(VERSION 3.24)

project(Window)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DWINDOW_EXPORT)

# Find and link OpenGL
find_package(OpenGL REQUIRED)

# spdlog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

add_library(${PROJECT_NAME} SHARED
	Window/include/Window.hpp
    Window/src/Window.cpp
	Events/include/Event.hpp
	Events/src/Event.cpp
	Events/include/EventType.hpp
	Events/include/CursorMoveEvent.hpp
	Events/src/CursorMoveEvent.cpp
	Events/include/FramebufferResizeEvent.hpp
	Events/src/FramebufferResizeEvent.cpp
	Events/include/KeyPressEvent.hpp
	Events/src/KeyPressEvent.cpp
)

#target_include_directories(${PROJECT_NAME} PUBLIC
include_directories(
    Window//include//
    Events//include//
    ..//ExternalGraphicsLibs//glfw//include//
    ..//ExternalGraphicsLibs//glfw//
    ..//ExternalGraphicsLibs//glad//include//
	..//ExternalGraphicsLibs//glm//
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} PRIVATE
    ExternalGraphicsLibs
	spdlog::spdlog
)

add_dependencies(${PROJECT_NAME} 
	ExternalGraphicsLibs
)