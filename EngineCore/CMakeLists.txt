cmake_minimum_required(VERSION 3.24)

project(EngineCore)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DENGINECORE_EXPORT)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${EXEC_NAME} OpenGL::GL)
if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${EXEC_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()

add_library(${PROJECT_NAME} 
    SHARED
	    GLFWWindow/include/GLFWWindow.hpp
        GLFWWindow/src/GLFWWindow.cpp
        GLFWWindow/include/GLFWWindowImpl.hpp
        GLFWWindow/src/GLFWWindowImpl.cpp
	    Events/include/Event.hpp
	    Events/src/Event.cpp
	    Events/include/EventType.hpp
	    Events/include/MouseEvents.hpp
	    Events/src/MouseEvents.cpp
	    Events/include/FramebufferEvents.hpp
	    Events/src/FramebufferEvents.cpp
	    Events/include/KeyEvents.hpp
	    Events/src/KeyEvents.cpp
	    Events/include/EventDispatcher.hpp
	    Events/src/EventDispatcher.cpp
	    MouseAndKeyCodes/include/MouseCodes.hpp
	    MouseAndKeyCodes/include/KeyCodes.hpp
        EngineRunner/include/EngineRunner.hpp
	    EngineRunner/src/EngineRunner.cpp
        EngineRunner/include/EngineRunnerImpl.hpp
	    EngineRunner/src/EngineRunnerImpl.cpp
)

# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/GLFWWindow 
    PREFIX 
        "GLFWWindow" 
    FILES
        GLFWWindow/include/GLFWWindow.hpp
        GLFWWindow/src/GLFWWindow.cpp
        GLFWWindow/include/GLFWWindowImpl.hpp
        GLFWWindow/src/GLFWWindowImpl.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Events 
    PREFIX 
        "Events" 
    FILES
        Events/include/Event.hpp
        Events/src/Event.cpp
        Events/include/EventType.hpp
        Events/include/MouseEvents.hpp
        Events/src/MouseEvents.cpp
        Events/include/FramebufferEvents.hpp
        Events/src/FramebufferEvents.cpp
        Events/include/KeyEvents.hpp
        Events/src/KeyEvents.cpp
        Events/include/EventDispatcher.hpp
	    Events/src/EventDispatcher.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/MouseAndKeyCodes 
    PREFIX 
        "MouseAndKeyCodes" 
    FILES
        MouseAndKeyCodes/include/MouseCodes.hpp
        MouseAndKeyCodes/include/KeyCodes.hpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/EngineRunner
    PREFIX
        "EngineRunner"
    FILES
        EngineRunner/include/EngineRunner.hpp
	    EngineRunner/src/EngineRunner.cpp
        EngineRunner/include/EngineRunnerImpl.hpp
	    EngineRunner/src/EngineRunnerImpl.cpp
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ..//ExternalGraphicsLibs//glfw//include//
        ..//ExternalGraphicsLibs//glfw//
        ..//ExternalGraphicsLibs//glad//include//
	    ..//ExternalGraphicsLibs//glm//
        ..//Utils//precompiled_headers//include//
        ..//Renderer//include//
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        Utils
        ExternalGraphicsLibs
        Renderer
)

add_dependencies(${PROJECT_NAME} 
    Utils
	ExternalGraphicsLibs
    Renderer
)

# Enable precompiled headers
target_precompile_headers(${PROJECT_NAME} 
    REUSE_FROM
        Utils
)