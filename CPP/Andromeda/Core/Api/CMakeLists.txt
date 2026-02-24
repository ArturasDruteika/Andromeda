cmake_minimum_required(VERSION 3.24)

project(Api LANGUAGES CXX)

# Static (header-only) library
add_library(${PROJECT_NAME} INTERFACE)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)

# ==== Camera ====
set(CAMERA_HEADERS
    Andromeda/Space/Camera/ICamera.hpp
    Andromeda/Space/Camera/IPerspectiveControl.hpp
    Andromeda/Space/Camera/ICameraView.hpp
    Andromeda/Space/Camera/ICameraController.hpp
)

# ==== Colors ====
set(COLORS_HEADERS
    Andromeda/Space/Colors/Colors.hpp
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

# ==== Light ====
set(LIGHT_HEADERS
    Andromeda/Space/Light/IDirectionalLight.hpp
    Andromeda/Space/Light/IPointLight.hpp
    Andromeda/Space/Light/ILight.hpp
    Andromeda/Space/Light/ISpotLight.hpp
    Andromeda/Space/Light/LightTypes.hpp
)

# ==== Materials ====
set(MATERIALS_HEADERS
    Andromeda/Materials/IMaterial.hpp
)

# ==== Objects ====
set(OBJECTS_HEADERS
    Andromeda/Space/Objects/ICameraObject.hpp
    Andromeda/Space/Objects/ICube.hpp
    Andromeda/Space/Objects/IGeometricObject.hpp
    Andromeda/Space/Objects/ILightObject.hpp
    Andromeda/Space/Objects/IMesh.hpp
    Andromeda/Space/Objects/IObject.hpp
    Andromeda/Space/Objects/ISkyroom.hpp
    Andromeda/Space/Objects/ISphere.hpp
)

# ==== Platform ====
set(PLATFORM_HEADERS
    Andromeda/Platform/IPlatform.hpp
)

# ==== Renderer ====
set(RENDERER_HEADERS
    Andromeda/Renderer/IGridControl.hpp
    Andromeda/Renderer/IIlluminationControl.hpp
    Andromeda/Renderer/IRenderer.hpp
    Andromeda/Renderer/ISizeControl.hpp
)

# ==== Scene ====
set(SCENE_HEADERS
    Andromeda/Space/Scene/ICameraHandler.hpp
    Andromeda/Space/Scene/IScene.hpp
    Andromeda/Space/Scene/ISceneEnvironment.hpp
    Andromeda/Space/Scene/ISceneLighting.hpp
    Andromeda/Space/Scene/ISceneObjects.hpp
    Andromeda/Space/Scene/ISceneState.hpp
    Andromeda/Space/Scene/IUpdateHooks.hpp
    Andromeda/Space/Scene/ISceneUpdateHooks.hpp
)

# ==== SceneGraph ====
set(SCENE_GRAPH_HEADERS
    Andromeda/Space/SceneGraph/ISceneComponent.hpp
    Andromeda/Space/SceneGraph/ISceneNode.hpp
)

# ==== Transformations ====
set(TRANSFORMATION_HEADERS
    Andromeda/Space/Transformations/IRotatable.hpp
    Andromeda/Space/Transformations/IScalable.hpp
    Andromeda/Space/Transformations/ITransformable.hpp
    Andromeda/Space/Transformations/ITranslatable.hpp
    Andromeda/Space/Transformations/TransformationTypes.hpp
)

# ==== Vertices ====
set(VERTICES_HEADERS
    Andromeda/Space/Vertices/Vertex.hpp
)

# ==== Window ====
set(WINDOW_HEADERS
    Andromeda/Window/Events/EventType.hpp
    Andromeda/Window/Events/IEvent.hpp
    Andromeda/Window/Events/IFrameBufferEvents.hpp
    Andromeda/Window/Events/IKeyEvents.hpp
    Andromeda/Window/Events/IMouseEvents.hpp
    Andromeda/Window/MouseAndKeyCodes/KeyCodes.hpp
    Andromeda/Window/MouseAndKeyCodes/MouseCodes.hpp
    Andromeda/Window/Window/IWindow.hpp
)

target_sources(${PROJECT_NAME}
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
            ${CAMERA_HEADERS}
            ${COLORS_HEADERS}
            ${COMPONENTS_HEADERS}
            ${ENGINE_HEADERS}
            ${GRAPHICS_CONTEXT_HEADERS}
            ${OBJECTS_HEADERS}
            ${PLATFORM_HEADERS}
            ${RENDERER_HEADERS}
            ${SCENE_HEADERS}
            ${SCENE_GRAPH_HEADERS}
            ${WINDOW_HEADERS}
            ${LIGHT_HEADERS}
            ${MATERIALS_HEADERS}
            ${TRANSFORMATION_HEADERS}
            ${VERTICES_HEADERS}
)

target_include_directories(${PROJECT_NAME} 
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Math
)

# ===== Visual Studio filters (Solution Explorer groups) =====
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Space/Camera
    PREFIX
        "Camera"
    FILES
        ${CAMERA_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Space/Colors
    PREFIX
        "Colors"
    FILES
        ${COLORS_HEADERS}
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
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Space/Light
    PREFIX
        "Light"
    FILES
        ${LIGHT_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Space/Materials
    PREFIX
        "Materials"
    FILES
        ${MATERIAL_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Space/Objects
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
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Space/Scene
    PREFIX
        "Scene"
    FILES
        ${SCENE_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Space/SceneGraph
    PREFIX
        "SceneGraph"
    FILES
        ${SCENE_GRAPH_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Space/Transformations
    PREFIX
        "Transformations"
    FILES
        ${TRANSFORMATION_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Space/Vertices
    PREFIX
        "Vertices"
    FILES
        ${VERTICES_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/Window
    PREFIX
        "Window"
    FILES
        ${WINDOW_HEADERS}
)
