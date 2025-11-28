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

# ==== Objects ====
set(OBJECTS_HEADERS
    Andromeda/Objects/ICameraObject.hpp
    Andromeda/Objects/ICube.hpp
    Andromeda/Objects/IGeometricObject.hpp
    Andromeda/Objects/ILightObject.hpp
    Andromeda/Objects/ILuminous.hpp
    Andromeda/Objects/IMesh.hpp
    Andromeda/Objects/IObject.hpp
    Andromeda/Objects/ISkyroom.hpp
    Andromeda/Objects/ISphere.hpp
    Andromeda/Objects/ITransformable.hpp
)

# ==== Platform ====
set(PLATFORM_HEADERS
    Andromeda/Platform/IPlatform.hpp
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
    Andromeda/Scene/ICameraHandler.hpp
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
            ${OBJECTS_HEADERS}
            ${PLATFORM_HEADERS}
            ${RENDERER_HEADERS}
            ${SCENE_HEADERS}
            ${WINDOW_HEADERS}
)

target_include_directories(${PROJECT_NAME} 
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Math
        Space
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
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Objects
    PREFIX
        "Objects"
    FILES
        ${OBJECTS_HEADERS}
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
