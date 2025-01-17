cmake_minimum_required(VERSION 3.24)

project(Context)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DCONTEXT_EXPORT)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${EXEC_NAME} OpenGL::GL)
if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${EXEC_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()

add_library(${PROJECT_NAME} 
    SHARED
        GLFWContext/include/GLFWContext.hpp
	    GLFWContext/src/GLFWContext.cpp
        GLFWContext/include/GLFWContextImpl.hpp
	    GLFWContext/src/GLFWContextImpl.cpp
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ..//Utils//PrecompiledHeaders//include//
        ..//ExternalGraphicsLibs//glfw//include//
        ..//ExternalGraphicsLibs//glfw//
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        Utils
        ExternalGraphicsLibs
)

add_dependencies(${PROJECT_NAME} 
    Utils
	ExternalGraphicsLibs
)

# Enable precompiled headers
target_precompile_headers(${PROJECT_NAME} 
    REUSE_FROM
        Utils
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/GLFWContext
    PREFIX
        "GLFWContext"
    FILES
        GLFWContext/include/GLFWContext.hpp
	    GLFWContext/src/GLFWContext.cpp
        GLFWContext/include/GLFWContextImpl.hpp
	    GLFWContext/src/GLFWContextImpl.cpp
)