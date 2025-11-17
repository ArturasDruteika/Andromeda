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

# SPDLog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)


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

# ==== Engine ====
set(ENGINE_HEADERS
    Engine/include/Engine.hpp
)

set(ENGINE_SOURCES
    Engine/src/Engine.cpp
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
        ${ENGINE_HEADERS}
        ${ENGINE_SOURCES}
        ${MACRO_EXPORTS_HEADERS}
        ${RENDERING_WINDOWS_HEADERS}
        ${RENDERING_WINDOWS_SOURCES}
)

target_compile_definitions(EngineCore 
    PRIVATE 
        ANDROMEDA_ENGINECORE_BUILD
)

# Include dirs (alphabetical)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ../Context/GLFWContext/include/
        ../Math/Constants/include/
        ../Math/Trigonometry/include/
        ../Api/Engine/
        ../Rendering/Attributes/include/
        ../Rendering/Camera/Cameras/include/
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
        Context
        ExternalGraphicsLibs
        OpenGL::GL
        Rendering
        Window
        glfw
        imgui
        spdlog::spdlog
    PUBLIC
        PrecompiledHeaders
        Math
        Api

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


### Post builds
# SPDLog
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if(MSVC)
        add_custom_command(
            TARGET 
                ${PROJECT_NAME} POST_BUILD 
            COMMAND 
                ${CMAKE_COMMAND} ARGS -E copy_if_different
                ${spdlog_root_path}//bin//$<$<CONFIG:debug>:spdlogd.dll>$<$<CONFIG:release>:spdlog.dll>
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    else()
        add_custom_command(
            TARGET 
                ${PROJECT_NAME} POST_BUILD 
            COMMAND 
                ${CMAKE_COMMAND} ARGS -E copy_if_different
                ${spdlog_root_path}//bin//$<$<CONFIG:debug>:spdlogd.dll>$<$<CONFIG:release>:spdlog.dll>
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endif()
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        # Copy and rename directly to the SONAME the loader expects
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${spdlog_root_path}/bin/$<$<CONFIG:Debug>:libspdlogd.so.1.15.3>$<$<CONFIG:Release>:libspdlog.so.1.15.3>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/$<$<CONFIG:Debug>:libspdlogd.so.1.15>$<$<CONFIG:Release>:libspdlog.so.1.15>
    )
endif()

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
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine
    PREFIX
        "Engine"
    FILES
        ${ENGINE_HEADERS}
        ${ENGINE_SOURCES}
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
