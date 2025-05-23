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
	    Application/include/Application.hpp
        Application/src/Application.cpp
        Application/include/ApplicationImpl.hpp
        Application/src/ApplicationImpl.cpp
        Application/include/CameraInputMapper.hpp
        Application/src/CameraInputMapper.cpp
        RenderingWindows/include/GraphicalModalWindow.hpp
        RenderingWindows/src/GraphicalModalWindow.cpp
        RenderingWindows/include/RendererWindowOpenGL.hpp
        RenderingWindows/src/RendererWindowOpenGL.cpp
        RenderingWindows/include/ImGuiDockspaceManager.hpp
        RenderingWindows/src/ImGuiDockspaceManager.cpp
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ..//Utils//PrecompiledHeaders//include//
        ..//glfw//include//
        ..//glfw//
        ..//Window//GLFWWindow//include//
        ..//Context//GLFWContext//include//
        ..//Rendering//Renderers//include//
        ..//Rendering//RenderableObjects//include//
        ..//Rendering//Vertices//include//
        ..//Rendering//Scene//include//
        ..//Rendering//OpenGLLoader//include//
        ..//Rendering//Attributes//include//
        ..//Rendering//Camera//include//
        ..//imgui//imgui//
	    ..//imgui//imgui//backends//
        ..//Space//DataTypes//include//
        ..//Space//Attributes//include//
        ..//Math//Constants//include//
        ..//Math//Trigonometry//include//
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        Utils
        glfw
        OpenGL::GL
        ExternalGraphicsLibs
        Window
        Context
        Rendering
        imgui
        Math
)

add_dependencies(${PROJECT_NAME} 
    Utils
    glfw
	ExternalGraphicsLibs
    Window
    Context
    Rendering
    imgui
    Math
)

# Enable precompiled headers
target_precompile_headers(${PROJECT_NAME} 
    REUSE_FROM
        Utils
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Application 
    PREFIX 
        "Application" 
    FILES
	    Application/include/Application.hpp
        Application/src/Application.cpp
        Application/include/ApplicationImpl.hpp
        Application/src/ApplicationImpl.cpp
        Application/include/CameraInputMapper.hpp
        Application/src/CameraInputMapper.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderingWindows 
    PREFIX 
        "RenderingWindows" 
    FILES
        RenderingWindows/include/GraphicalModalWindow.hpp
        RenderingWindows/src/GraphicalModalWindow.cpp
        RenderingWindows/include/RendererWindowOpenGL.hpp
        RenderingWindows/src/RendererWindowOpenGL.cpp
        RenderingWindows/include/ImGuiDockspaceManager.hpp
        RenderingWindows/src/ImGuiDockspaceManager.cpp
)