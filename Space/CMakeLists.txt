cmake_minimum_required(VERSION 3.24)

project(Space)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSPACE_EXPORT)

# SPDLog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)


# ==== Colors ====
set(COLORS_HEADERS
    Space/Colors/include/Colors.hpp
)

# ==== Light ====
set(LIGHT_HEADERS
    Space/Light/Abstracts/include/Light.hpp
    Space/Light/Abstracts/include/LuminousBehavior.hpp
    Space/Light/Abstracts/include/NonLuminousBehavior.hpp
    Space/Light/Interfaces/include/ILightBehavior.hpp
    Space/Light/LightTypes/include/DirectionalLight.hpp
    Space/Light/LightTypes/include/PointLight.hpp
    Space/Light/LightTypes/include/SpotLight.hpp
    Space/Light/Support/include/LightData.hpp
    Space/Light/Support/include/LightTypes.hpp
)

set(LIGHT_SOURCES
    Space/Light/Abstracts/src/Light.cpp
    Space/Light/Abstracts/src/LuminousBehavior.cpp
    Space/Light/Abstracts/src/NonLuminousBehavior.cpp
    Space/Light/Interfaces/src/ILightBehavior.cpp
    Space/Light/LightTypes/src/DirectionalLight.cpp
    Space/Light/LightTypes/src/PointLight.cpp
    Space/Light/LightTypes/src/SpotLight.cpp
    Space/Light/Support/src/LightData.cpp
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

# ==== Coordinates ====
set(COORDINATES_HEADERS
    Space/Coordinates/include/Points.hpp
)

# ==== Transformations ====
set(TRANSFORMATIONS_HEADERS
    Space/Transformations/include/TransformationTypes.hpp
)

# ==== Vertices ====
set(VERTICES_HEADERS
    Space/Vertices/include/Vertex.hpp
)

# ==== Target ====
add_library(${PROJECT_NAME}
    SHARED
        ${COLORS_HEADERS}
        ${LIGHT_HEADERS}
        ${LIGHT_SOURCES}
        ${MACRO_EXPORTS_HEADERS}
        ${MATERIALS_HEADERS}
        ${MATERIALS_SOURCES}
        ${COORDINATES_HEADERS}
        ${TRANSFORMATIONS_HEADERS}
        ${VERTICES_HEADERS}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# ==== Link Libraries ====
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        PrecompiledHeaders
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
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Colors
    PREFIX
        "Colors"
    FILES
        ${COLORS_HEADERS}
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
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Coordinates
    PREFIX
        "Coordinates"
    FILES
        ${COORDINATES_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Transformations
    PREFIX
        "Transformations"
    FILES
        ${TRANSFORMATIONS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Vertices
    PREFIX
        "Vertices"
    FILES
        ${VERTICES_HEADERS}
)
