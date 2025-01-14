cmake_minimum_required(VERSION 3.24)

project(Environment)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DENVIRONMENT_EXPORT)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${EXEC_NAME} OpenGL::GL)
if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${EXEC_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()

add_library(${PROJECT_NAME} 
    SHARED
	    Scene/include/OpenGLScene.hpp
		Scene/src/OpenGLScene.cpp
        Scene/include/OpenGLSceneImpl.hpp
		Scene/src/OpenGLSceneImpl.cpp
        RenderableObjects/include/OpenGLRenderableObject.hpp
		RenderableObjects/src/OpenGLRenderableObject.cpp
        RenderableObjects/include/OpenGLRenderableObjectImpl.hpp
		RenderableObjects/src/OpenGLRenderableObjectImpl.cpp
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ..//Utils//PrecompiledHeaders//include//
        ..//Utils//FileOperations//include//
        ..//ExternalGraphicsLibs//glad//include//
	    ..//ExternalGraphicsLibs//glm//
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
        ${CMAKE_CURRENT_SOURCE_DIR}/Scene
    PREFIX
        "Scene"
    FILES
        Scene/include/OpenGLScene.hpp
		Scene/src/OpenGLScene.cpp
        Scene/include/OpenGLSceneImpl.hpp
		Scene/src/OpenGLSceneImpl.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderableObjects
    PREFIX
        "RenderableObjects"
    FILES
        RenderableObjects/include/OpenGLRenderableObject.hpp
		RenderableObjects/src/OpenGLRenderableObject.cpp
        RenderableObjects/include/OpenGLRenderableObjectImpl.hpp
		RenderableObjects/src/OpenGLRenderableObjectImpl.cpp
)
