cmake_minimum_required(VERSION 3.24)

project(Space)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSPACE_EXPORT)


add_library(${PROJECT_NAME} 
    SHARED
        Scene/include/Scene.hpp
        Scene/src/Scene.cpp
        Scene/include/SceneImpl.hpp
        Scene/src/SceneImpl.cpp

        DataTypes/include/Points.hpp

        Objects/include/ObjectBase.hpp
        Objects/src/ObjectBase.cpp
        Objects/include/ObjectTypes.hpp
        Objects/include/Sphere.hpp
        Objects/src/Sphere.cpp
        Objects/include/SphereImpl.hpp
        Objects/src/SphereImpl.cpp

        Attributes/include/Colors.hpp
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ..//Utils//PrecompiledHeaders//include//
        ..//Math//LinearAlgebra//include//
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        Utils
        Math
)

add_dependencies(${PROJECT_NAME} 
    Utils
    Math
)

# Enable precompiled headers
target_precompile_headers(${PROJECT_NAME} 
    REUSE_FROM
        Utils
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Scene 
    PREFIX 
        "Scene" 
    FILES
        Scene/include/Scene.hpp
        Scene/src/Scene.cpp
        Scene/include/SceneImpl.hpp
        Scene/src/SceneImpl.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/DataTypes 
    PREFIX 
        "DataTypes" 
    FILES
        DataTypes/include/Points.hpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Objects 
    PREFIX 
        "Objects" 
    FILES
        Objects/include/ObjectBase.hpp
        Objects/src/ObjectBase.cpp
        Objects/include/ObjectTypes.hpp
        Objects/include/Sphere.hpp
        Objects/src/Sphere.cpp
        Objects/include/SphereImpl.hpp
        Objects/src/SphereImpl.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Attributes 
    PREFIX 
        "Attributes" 
    FILES
        Attributes/include/Colors.hpp
)