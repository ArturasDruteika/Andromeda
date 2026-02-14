cmake_minimum_required(VERSION 3.24)

project(GraphicsContext)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${EXEC_NAME} OpenGL::GL)
if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${EXEC_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()

# ==== GraphicsContext ====
set(GRAPHICS_CONTEXT_HEADERS
    GraphicsContext/include/GraphicsContextGLFW.hpp
)

set(GRAPHICS_CONTEXT_SOURCES
    GraphicsContext/src/GraphicsContextGLFW.cpp
)

add_library(${PROJECT_NAME} 
    STATIC
        ${GRAPHICS_CONTEXT_HEADERS}
        ${GRAPHICS_CONTEXT_SOURCES}
)

# SPDLog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../3rdParty/spdlog/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../3rdParty/spdlog/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ..//glfw//include//
        ..//glfw//
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        PrecompiledHeaders
        Api
        Window
        Glad
        glfw
        OpenGL::GL
        spdlog::spdlog
)

add_dependencies(${PROJECT_NAME} 
	glfw
    Glad
    Window
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsContext
    PREFIX
        "GraphicsContext"
    FILES
        ${GRAPHICS_CONTEXT_HEADERS}
        ${GRAPHICS_CONTEXT_SOURCES}
)