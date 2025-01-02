cmake_minimum_required(VERSION 3.24)

project(Renderer)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DRENDERER_EXPORT)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${EXEC_NAME} OpenGL::GL)
if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${EXEC_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()

add_library(${PROJECT_NAME} 
    SHARED
	    include/Renderer.hpp
		src/Renderer.cpp
		include/RendererImpl.hpp
		src/RendererImpl.cpp
)

# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        include/Renderer.hpp
		src/Renderer.cpp
		include/RendererImpl.hpp
		src/RendererImpl.cpp
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ..//Utils//precompiled_headers//include//
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