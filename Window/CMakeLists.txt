cmake_minimum_required(VERSION 3.24)

project(Window)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DWINDOW_EXPORT)

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
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ..//Utils//PrecompiledHeaders//include//
        ..//ExternalGraphicsLibs//glfw//include//
        ..//ExternalGraphicsLibs//glfw//

)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        Utils
        ExternalGraphicsLibs
)

add_dependencies(${PROJECT_NAME} 
    Utils
    ExternalGraphicsLibs
)

# Enable precompiled headers
target_precompile_headers(${PROJECT_NAME} 
    REUSE_FROM
        Utils
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
