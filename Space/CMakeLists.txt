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


# ==== Attributes ====
set(ATTRIBUTES_HEADERS
    Attributes/include/Colors.hpp
)

# ==== DataTypes ====
set(DATATYPES_HEADERS
    DataTypes/include/Points.hpp
)

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    MacroExports/include/MacroExports.hpp
)

# ==== Objects ====
set(OBJECTS_HEADERS
    Objects/include/Cube.hpp
    Objects/include/CubeImpl.hpp
    Objects/include/ObjectBase.hpp
    Objects/include/ObjectTypes.hpp
    Objects/include/Sphere.hpp
    Objects/include/SphereImpl.hpp
)

set(OBJECTS_SOURCES
    Objects/src/Cube.cpp
    Objects/src/CubeImpl.cpp
    Objects/src/ObjectBase.cpp
    Objects/src/Sphere.cpp
    Objects/src/SphereImpl.cpp
)

# ==== Scene ====
set(SCENE_HEADERS
    Scene/include/Scene.hpp
    Scene/include/SceneImpl.hpp
)

set(SCENE_SOURCES
    Scene/src/Scene.cpp
    Scene/src/SceneImpl.cpp
)

# ==== Target ====
add_library(${PROJECT_NAME}
    SHARED
        ${ATTRIBUTES_HEADERS}
        ${DATATYPES_HEADERS}
        ${MACRO_EXPORTS_HEADERS}
        ${OBJECTS_HEADERS}
        ${OBJECTS_SOURCES}
        ${SCENE_HEADERS}
        ${SCENE_SOURCES}
)

# ==== Include Directories ====
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ..//Math//LinearAlgebra//include//
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
        ${CMAKE_CURRENT_SOURCE_DIR}/Attributes
    PREFIX
        "Attributes"
    FILES
        ${ATTRIBUTES_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/DataTypes
    PREFIX
        "DataTypes"
    FILES
        ${DATATYPES_HEADERS}
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
        ${CMAKE_CURRENT_SOURCE_DIR}/Objects
    PREFIX
        "Objects"
    FILES
        ${OBJECTS_HEADERS}
        ${OBJECTS_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Scene
    PREFIX
        "Scene"
    FILES
        ${SCENE_HEADERS}
        ${SCENE_SOURCES}
)
