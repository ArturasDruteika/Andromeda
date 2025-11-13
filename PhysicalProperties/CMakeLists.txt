cmake_minimum_required(VERSION 3.24)

project(PhysicalProperties)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DPHYSICAL_PROPERTIES_EXPORT)

# SPDLog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)


# ==== Colors ====
set(COLORS_HEADERS
    Colors/include/Colors.hpp
)

# ==== Light ====
set(LIGHT_HEADERS
    Light/Abstracts/include/Light.hpp
    Light/Abstracts/include/LuminousBehavior.hpp
    Light/Abstracts/include/NonLuminousBehavior.hpp
    Light/Interfaces/include/ILightBehavior.hpp
    Light/LightTypes/include/DirectionalLight.hpp
    Light/LightTypes/include/PointLight.hpp
    Light/LightTypes/include/SpotLight.hpp
    Light/Support/include/LightData.hpp
    Light/Support/include/LightTypes.hpp
)

set(LIGHT_SOURCES
    Light/Abstracts/src/Light.cpp
    Light/Abstracts/src/LuminousBehavior.cpp
    Light/Abstracts/src/NonLuminousBehavior.cpp
    Light/Interfaces/src/ILightBehavior.cpp
    Light/LightTypes/src/DirectionalLight.cpp
    Light/LightTypes/src/PointLight.cpp
    Light/LightTypes/src/SpotLight.cpp
    Light/Support/src/LightData.cpp
)

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    MacroExports/include/MacroExports.hpp
)

# ==== Materials ====
set(MATERIALS_HEADERS
    Materials/include/Materials.hpp
    Materials/include/MaterialsLibrary.hpp
    Materials/include/MaterialTypes.hpp
)

set(MATERIALS_SOURCES
    Materials/src/Materials.cpp
    Materials/src/MaterialsLibrary.cpp
)

# ==== Space ====
set(SPACE_HEADERS
    Space/include/Points.hpp
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
        ${SPACE_HEADERS}
)

# ==== Include Directories ====
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ..//Math//LinearAlgebra//include//
        ..//Utils//FileOperations//include//
        ..//Utils//nlohmann_json//include//
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


# ==== IDE Organization ====
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Colors
    PREFIX
        "Colors"
    FILES
        ${COLORS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Light
    PREFIX
        "Light"
    FILES
        ${LIGHT_HEADERS}
        ${LIGHT_SOURCES}
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
        ${CMAKE_CURRENT_SOURCE_DIR}/Materials
    PREFIX
        "Materials"
    FILES
        ${MATERIALS_HEADERS}
        ${MATERIALS_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Space
    PREFIX
        "Space"
    FILES
        ${SPACE_HEADERS}
        ${SPACE_SOURCES}
)
