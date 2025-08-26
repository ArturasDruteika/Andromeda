cmake_minimum_required(VERSION 3.24)

project(EngineCore)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DENGINECORE_EXPORT)

# OpenGL
find_package(OpenGL REQUIRED)
if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()


# ==== Application ====
set(APPLICATION_HEADERS
    Application/include/Application.hpp
    Application/include/ApplicationImpl.hpp
    Application/include/CameraInputMapper.hpp
)

set(APPLICATION_SOURCES
    Application/src/Application.cpp
    Application/src/ApplicationImpl.cpp
    Application/src/CameraInputMapper.cpp
)

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    MacroExports/include/MacroExports.hpp
)

# ==== RenderingWindows ====
set(RENDERING_WINDOWS_HEADERS
    RenderingWindows/include/GraphicalModalWindow.hpp
    RenderingWindows/include/ImGuiDockspaceManager.hpp
    RenderingWindows/include/RendererWindowOpenGL.hpp
)

set(RENDERING_WINDOWS_SOURCES
    RenderingWindows/src/GraphicalModalWindow.cpp
    RenderingWindows/src/ImGuiDockspaceManager.cpp
    RenderingWindows/src/RendererWindowOpenGL.cpp
)


# ==== Target ====
add_library(${PROJECT_NAME}
    SHARED
        ${APPLICATION_HEADERS}
        ${APPLICATION_SOURCES}
        ${MACRO_EXPORTS_HEADERS}
        ${RENDERING_WINDOWS_HEADERS}
        ${RENDERING_WINDOWS_SOURCES}
)

# Include dirs (alphabetical)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ../Context/GLFWContext/include/
        ../Math/Constants/include/
        ../Math/Trigonometry/include/
        ../Rendering/Attributes/include/
        ../Rendering/Camera/include/
        ../Rendering/Light/LightTypes/include/
        ../Rendering/OpenGLLoader/include/
        ../Rendering/RenderableObjects/Interfaces/include/
        ../Rendering/Renderers/Renderers/include/
        ../Rendering/Scene/Interfaces/include/
        ../Rendering/Scene/Scenes/include/
        ../Rendering/Vertices/include/
        ../Window/GLFWWindow/include/
        ../glfw/
        ../glfw/include/
        ../imgui/imgui/
        ../imgui/imgui/backends/
)

# Link libraries (alphabetical)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        PrecompiledHeaders
        Math
        Context
        ExternalGraphicsLibs
        OpenGL::GL
        Rendering
        Window
        glfw
        imgui
)

# Explicit build ordering (alphabetical)
add_dependencies(${PROJECT_NAME}
    Context
    ExternalGraphicsLibs
    Math
    Rendering
    Utils
    Window
    glfw
    imgui
)


# ==== IDE Organization ====
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Application
    PREFIX
        "Application"
    FILES
        ${APPLICATION_HEADERS}
        ${APPLICATION_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/MacroExports
    PREFIX
        "MacroExports"
    FILES
        ${MACRO_EXPORTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderingWindows
    PREFIX
        "RenderingWindows"
    FILES
        ${RENDERING_WINDOWS_HEADERS}
        ${RENDERING_WINDOWS_SOURCES}
)
