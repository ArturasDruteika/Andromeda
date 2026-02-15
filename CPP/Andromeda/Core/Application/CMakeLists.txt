cmake_minimum_required(VERSION 3.24)

project(Application)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DAPPLICATION_EXPORT)


# SPDLog


# ==== ApplicationGLFW ====
set(APPLICATION_HEADERS
    Application/include/Application.hpp
)

set(APPLICATION_SOURCES
    Application/src/Application.cpp
)

add_library(${PROJECT_NAME} 
    SHARED
        ${APPLICATION_HEADERS}
        ${APPLICATION_SOURCES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE 
        ANDROMEDA_API_BUILD
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        PrecompiledHeaders
        spdlog::spdlog
    PUBLIC
        Engine
        Platform
        Api
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}
    PREFIX 
        "Application" 
    FILES
        ${APPLICATION_HEADERS}
        ${APPLICATION_SOURCES}
)
