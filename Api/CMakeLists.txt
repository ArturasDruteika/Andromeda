cmake_minimum_required(VERSION 3.24)

project(Api LANGUAGES CXX)

# Static (header-only) library
add_library(${PROJECT_NAME} INTERFACE)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)

# ==== Camera ====
set(CAMERA_HEADERS
    Camera/ICamera.hpp
    Camera/IPerspectiveControl.hpp
    Camera/ICameraView.hpp
    Camera/ICameraController.hpp
)

# ==== Engine ====
set(ENGINE_HEADERS
    Engine/IEngine.hpp
    Engine/GraphicsBackend.hpp
)

# ==== RenderableObjects ====
set(RENDERABLE_OBJECTS_HEADERS
    RenderableObjects/ICube.hpp
    RenderableObjects/ILuminous.hpp
    RenderableObjects/IMesh.hpp
    RenderableObjects/IRenderableObject.hpp
    RenderableObjects/ISkyroom.hpp
    RenderableObjects/ISphere.hpp
    RenderableObjects/ITransformable.hpp
)

# ==== Renderer ====
set(RENDERER_HEADERS
    Renderer/ICameraControl.hpp
    Renderer/IGridControl.hpp
    Renderer/IIlluminationControl.hpp
    Renderer/IRenderer.hpp
    Renderer/ISizeControl.hpp
)

# ==== Scene ====
set(SCENE_HEADERS
    Scene/IScene.hpp
    Scene/ISceneEnvironment.hpp
    Scene/ISceneLighting.hpp
    Scene/ISceneObjects.hpp
    Scene/ISceneState.hpp
)

target_sources(${PROJECT_NAME}
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
            ${CAMERA_HEADERS}
            ${ENGINE_HEADERS}
            ${RENDERABLE_OBJECTS_HEADERS}
            ${RENDERER_HEADERS}
            ${SCENE_HEADERS}
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
        ${CMAKE_CURRENT_SOURCE_DIR}/Camera
    PREFIX
        "Camera"
    FILES
        ${CAMERA_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine
    PREFIX
        "Engine"
    FILES
        ${ENGINE_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderableObjects
    PREFIX
        "RenderableObjects"
    FILES
        ${RENDERABLE_OBJECTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Renderer
    PREFIX
        "Renderer"
    FILES
        ${RENDERER_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Scene
    PREFIX
        "Scene"
    FILES
        ${SCENE_HEADERS}
)
