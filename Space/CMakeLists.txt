cmake_minimum_required(VERSION 3.24)

project(Space)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSPACE_EXPORT)

if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${EXEC_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()

add_library(${PROJECT_NAME} 
    SHARED
        Scene/include/Scene.hpp
        Scene/src/Scene.cpp
        Scene/include/SceneImpl.hpp
        Scene/src/SceneImpl.cpp
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ..//Utils//PrecompiledHeaders//include//
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        Utils
)

add_dependencies(${PROJECT_NAME} 
    Utils
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