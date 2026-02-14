cmake_minimum_required(VERSION 3.24)

project(Space)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSPACE_EXPORT)

# SPDLog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../3rdParty/spdlog/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../3rdParty/spdlog/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)


# ==== Camera ====
set(CAMERA_HEADERS
    Space/Camera/include/PerspectiveControl.hpp
    Space/Camera/include/CameraView.hpp
    Space/Camera/include/CameraController.hpp
    Space/Camera/include/Camera.hpp
)

set(CAMERA_SOURCES
    Space/Camera/src/PerspectiveControl.cpp
    Space/Camera/src/CameraView.cpp
    Space/Camera/src/CameraController.cpp
    Space/Camera/src/Camera.cpp
)

# ==== Coordinates ====
set(COORDINATES_HEADERS
    Space/Coordinates/include/Points.hpp
)

# ==== Light ====
set(LIGHT_HEADERS
    Space/Light/include/Light.hpp
    Space/Light/include/DirectionalLight.hpp
    Space/Light/include/PointLight.hpp
    Space/Light/include/SpotLight.hpp
    Space/Light/include/LightData.hpp
)

set(LIGHT_SOURCES
    Space/Light/src/Light.cpp
    Space/Light/src/DirectionalLight.cpp
    Space/Light/src/PointLight.cpp
    Space/Light/src/SpotLight.cpp
    Space/Light/src/LightData.cpp
)

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    Space/MacroExports/include/MacroExports.hpp
)

# ==== Materials ====
set(MATERIALS_HEADERS
    Space/Materials/include/Materials.hpp
    Space/Materials/include/MaterialsLibrary.hpp
    Space/Materials/include/MaterialTypes.hpp
)

set(MATERIALS_SOURCES
    Space/Materials/src/Materials.cpp
    Space/Materials/src/MaterialsLibrary.cpp
)

# ==== Objects ====
set(OBJECTS_HEADERS
    Space/Objects/include/CameraObject.hpp
    Space/Objects/include/Cube.hpp
    Space/Objects/include/GeometricObject.hpp
    Space/Objects/include/LightObject.hpp
    Space/Objects/include/Mesh.hpp
    Space/Objects/include/Object.hpp
    Space/Objects/include/Skyroom.hpp
    Space/Objects/include/Sphere.hpp
    Space/Objects/include/SurfaceObject.hpp
)

set(OBJECTS_SOURCES
    Space/Objects/src/CameraObject.cpp
    Space/Objects/src/Cube.cpp
    Space/Objects/src/GeometricObject.cpp
    Space/Objects/src/LightObject.cpp
    Space/Objects/src/Mesh.cpp
    Space/Objects/src/Object.cpp
    Space/Objects/src/Skyroom.cpp
    Space/Objects/src/Sphere.cpp
    Space/Objects/src/SurfaceObject.cpp
)

# ==== Scene ====
set(SCENE_HEADERS
    Space/Scene/include/CameraHandler.hpp
    Space/Scene/include/Scene.hpp
    Space/Scene/include/SceneEnvironment.hpp
    Space/Scene/include/SceneLighting.hpp
    Space/Scene/include/SceneObjects.hpp
    Space/Scene/include/SceneState.hpp
)

set(SCENE_SOURCES
    Space/Scene/src/CameraHandler.cpp
    Space/Scene/src/Scene.cpp
    Space/Scene/src/SceneEnvironment.cpp
    Space/Scene/src/SceneLighting.cpp
    Space/Scene/src/SceneObjects.cpp
    Space/Scene/src/SceneState.cpp
)

# ==== SceneGraph ====
set(SCENE_GRAPH_HEADERS
    Space/SceneGraph/include/SceneComponent.hpp
    Space/SceneGraph/include/SceneNode.hpp
    Space/SceneGraph/include/ObjectComponent.hpp
    Space/SceneGraph/include/LightComponent.hpp
)

set(SCENE_GRAPH_SOURCES
    Space/SceneGraph/src/SceneComponent.cpp
    Space/SceneGraph/src/SceneNode.cpp
    Space/SceneGraph/src/ObjectComponent.cpp
    Space/SceneGraph/src/LightComponent.cpp
)

# ==== Transformations ====
set(TRANSFORMATIONS_HEADERS
    Space/Transformations/include/Rotatable.hpp
    Space/Transformations/include/Scalable.hpp
    Space/Transformations/include/Transformable.hpp
    Space/Transformations/include/TransformationTypes.hpp
    Space/Transformations/include/Translatable.hpp
)

set(TRANSFORMATIONS_SOURCES
    Space/Transformations/src/Rotatable.cpp
    Space/Transformations/src/Scalable.cpp
    Space/Transformations/src/Transformable.cpp
    Space/Transformations/src/Translatable.cpp
)

# ==== Target ====
add_library(${PROJECT_NAME}
    SHARED
        ${CAMERA_HEADERS}
        ${CAMERA_SOURCES}
        ${COORDINATES_HEADERS}
        ${LIGHT_HEADERS}
        ${LIGHT_SOURCES}
        ${MACRO_EXPORTS_HEADERS}
        ${MATERIALS_HEADERS}
        ${MATERIALS_SOURCES}
        ${OBJECTS_HEADERS}
        ${OBJECTS_SOURCES}
        ${SCENE_HEADERS}
        ${SCENE_SOURCES}
        ${SCENE_GRAPH_HEADERS}
        ${SCENE_GRAPH_SOURCES}
        ${TRANSFORMATIONS_HEADERS}
        ${TRANSFORMATIONS_SOURCES}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# ==== Link Libraries ====
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        PrecompiledHeaders
        Api
        Math
        Utils
        spdlog::spdlog
)

# ==== Dependencies ====
add_dependencies(${PROJECT_NAME}
    Math
    Utils
)


## Material properties
set(MATERIAL_JSON_FILENAME "material_properties.json")
set(MATERIAL_JSON_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/MaterialProperties/${MATERIAL_JSON_FILENAME}"
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(MATERIAL_JSON_OUTPUT_DIR "${CMAKE_ASSETS_OUTPUT_DIRECTORY}/$<CONFIG>/material_properties")
else()
    set(MATERIAL_JSON_OUTPUT_DIR "${CMAKE_ASSETS_OUTPUT_DIRECTORY}/material_properties")
endif()

set(MATERIAL_JSON_OUTPUT "${MATERIAL_JSON_OUTPUT_DIR}/${MATERIAL_JSON_FILENAME}")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory
        "${MATERIAL_JSON_OUTPUT_DIR}"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MATERIAL_JSON_SOURCE}"
        "${MATERIAL_JSON_OUTPUT}"

    COMMENT "Copying ${MATERIAL_JSON_FILENAME} to ${MATERIAL_JSON_OUTPUT_DIR}"
)


# ==== IDE Organization ====
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Camera
    PREFIX
        "Camera"
    FILES
        ${CAMERA_HEADERS}
        ${CAMERA_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Coordinates
    PREFIX
        "Coordinates"
    FILES
        ${COORDINATES_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Light
    PREFIX
        "Light"
    FILES
        ${LIGHT_HEADERS}
        ${LIGHT_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/MacroExports
    PREFIX
        "MacroExports"
    FILES
        ${MACRO_EXPORTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Materials
    PREFIX
        "Materials"
    FILES
        ${MATERIALS_HEADERS}
        ${MATERIALS_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Objects
    PREFIX
        "Objects"
    FILES
        ${OBJECTS_HEADERS}
        ${OBJECTS_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Scene
    PREFIX
        "Scene"
    FILES
        ${SCENE_HEADERS}
        ${SCENE_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/SceneGraph
    PREFIX
        "SceneGraph"
    FILES
        ${SCENE_GRAPH_HEADERS}
        ${SCENE_GRAPH_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Transformations
    PREFIX
        "Transformations"
    FILES
        ${TRANSFORMATIONS_HEADERS}
        ${TRANSFORMATIONS_SOURCES}
)
