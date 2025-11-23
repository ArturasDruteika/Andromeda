cmake_minimum_required(VERSION 3.24)

project(Api LANGUAGES CXX)

# Static (header-only) library
add_library(${PROJECT_NAME} INTERFACE)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)

# ==== Camera ====
set(CAMERA_HEADERS
    Andromeda/Camera/ICamera.hpp
    Andromeda/Camera/IPerspectiveControl.hpp
    Andromeda/Camera/ICameraView.hpp
    Andromeda/Camera/ICameraController.hpp
)

# ==== Components ====
set(COMPONENTS_HEADERS
    Andromeda/Components/GraphicsBackend.hpp
)

# ==== Engine ====
set(ENGINE_HEADERS
    Andromeda/Engine/IEngine.hpp
    Andromeda/Engine/GraphicsBackend.hpp
)

# ==== GraphicsContext ====
set(GRAPHICS_CONTEXT_HEADERS
    Andromeda/GraphicsContext/IGraphicsContext.hpp
)

# ==== Platform ====
set(PLATFORM_HEADERS
    Andromeda/Platform/IPlatform.hpp
)

# ==== RenderableObjects ====
set(RENDERABLE_OBJECTS_HEADERS
    Andromeda/RenderableObjects/ICube.hpp
    Andromeda/RenderableObjects/ILuminous.hpp
    Andromeda/RenderableObjects/IMesh.hpp
    Andromeda/RenderableObjects/IRenderableObject.hpp
    Andromeda/RenderableObjects/ISkyroom.hpp
    Andromeda/RenderableObjects/ISphere.hpp
    Andromeda/RenderableObjects/ITransformable.hpp
)

# ==== Renderer ====
set(RENDERER_HEADERS
    Andromeda/Renderer/ICameraControl.hpp
    Andromeda/Renderer/IGridControl.hpp
    Andromeda/Renderer/IIlluminationControl.hpp
    Andromeda/Renderer/IRenderer.hpp
    Andromeda/Renderer/ISizeControl.hpp
)

# ==== Scene ====
set(SCENE_HEADERS
    Andromeda/Scene/IScene.hpp
    Andromeda/Scene/ISceneEnvironment.hpp
    Andromeda/Scene/ISceneLighting.hpp
    Andromeda/Scene/ISceneObjects.hpp
    Andromeda/Scene/ISceneState.hpp
)

# ==== Window ====
set(WINDOW_HEADERS
    Andromeda/Window/EventType.hpp
    Andromeda/Window/IEvent.hpp
    Andromeda/Window/IWindow.hpp
)

target_sources(${PROJECT_NAME}
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
        FILES
            ${CAMERA_HEADERS}
            ${COMPONENTS_HEADERS}
            ${ENGINE_HEADERS}
            ${GRAPHICS_CONTEXT_HEADERS}
            ${PLATFORM_HEADERS}
            ${RENDERABLE_OBJECTS_HEADERS}
            ${RENDERER_HEADERS}
            ${SCENE_HEADERS}
            ${WINDOW_HEADERS}
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../Math/LinearAlgebra/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/../PhysicalProperties/Light/interfaces/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/../PhysicalProperties/Colors/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/../PhysicalProperties/Vertices/include/
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Math
        PhysicalProperties
)

# ===== Visual Studio filters (Solution Explorer groups) =====
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Camera
    PREFIX
        "Camera"
    FILES
        ${CAMERA_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Components
    PREFIX
        "Components"
    FILES
        ${COMPONENTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/GraphicsContext
    PREFIX
        "GraphicsContext"
    FILES
        ${GRAPHICS_CONTEXT_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Engine
    PREFIX
        "Engine"
    FILES
        ${ENGINE_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Platform
    PREFIX
        "Platform"
    FILES
        ${PLATFORM_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/RenderableObjects
    PREFIX
        "RenderableObjects"
    FILES
        ${RENDERABLE_OBJECTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Renderer
    PREFIX
        "Renderer"
    FILES
        ${RENDERER_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Scene
    PREFIX
        "Scene"
    FILES
        ${SCENE_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Window
    PREFIX
        "Window"
    FILES
        ${WINDOW_HEADERS}
)
