cmake_minimum_required(VERSION 3.24)

project(Rendering)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DRENDERING_EXPORT)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${EXEC_NAME} OpenGL::GL)
if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${EXEC_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()

add_library(${PROJECT_NAME} 
    SHARED
	    Renderers/include/OpenGLRenderer.hpp
		Renderers/src/OpenGLRenderer.cpp
        Renderers/include/OpenGLRendererImpl.hpp
		Renderers/src/OpenGLRendererImpl.cpp

        Shaders/include/OpenGLShader.hpp
		Shaders/src/OpenGLShader.cpp

        Scene/include/OpenGLScene.hpp
		Scene/src/OpenGLScene.cpp
        Scene/include/OpenGLSceneImpl.hpp
		Scene/src/OpenGLSceneImpl.cpp

        RenderableObjects/include/OpenGLRenderableObject.hpp
		RenderableObjects/src/OpenGLRenderableObject.cpp
        RenderableObjects/include/OpenGLRenderableObjectImpl.hpp
		RenderableObjects/src/OpenGLRenderableObjectImpl.cpp

		Vertices/include/VertexAttributes.hpp
        Vertices/include/VertexLayouts.hpp
		Vertices/src/VertexLayouts.cpp
        Vertices/include/VertexLayoutsImpl.hpp
		Vertices/src/VertexLayoutsImpl.cpp
        Vertices/include/Vertex.hpp

        OpenGLLoader/include/OpenGLLoader.hpp
		OpenGLLoader/src/OpenGLLoader.cpp
        OpenGLLoader/include/OpenGLLoaderImpl.hpp
		OpenGLLoader/src/OpenGLLoaderImpl.cpp

        Attributes/include/Points.hpp
        Attributes/include/Colors.hpp
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


### Post builds
# Define filenames
set(VERTEX_SHADER_FILENAME "vertex_shader.glsl")
set(FRAGMENT_SHADER_FILENAME "fragment_shader.glsl")

# Define source shader file paths
set(VERTEX_SHADER_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgramSources/${VERTEX_SHADER_FILENAME}")
set(FRAGMENT_SHADER_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgramSources/${FRAGMENT_SHADER_FILENAME}")

# Define the output directory (binary directory where executables are placed)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SHADER_OUTPUT_DIR "${CMAKE_ASSETS_OUTPUT_DIRECTORY}/$<CONFIG>/shader_program_sources")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(SHADER_OUTPUT_DIR "${CMAKE_ASSETS_OUTPUT_DIRECTORY}/shader_program_sources")
endif()

# Post-build step to copy shader files
add_custom_command(
    TARGET 
        ${PROJECT_NAME} POST_BUILD
    COMMAND 
        ${CMAKE_COMMAND} -E make_directory "${SHADER_OUTPUT_DIR}"
    COMMAND 
        ${CMAKE_COMMAND} -E copy_if_different
        "${VERTEX_SHADER_SOURCE}" "${SHADER_OUTPUT_DIR}/${VERTEX_SHADER_FILENAME}"
    COMMAND 
        ${CMAKE_COMMAND} -E copy_if_different
        "${FRAGMENT_SHADER_SOURCE}" "${SHADER_OUTPUT_DIR}/${FRAGMENT_SHADER_FILENAME}"
    COMMENT 
        "Creating directory and copying shader files to ${SHADER_OUTPUT_DIR}"
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Renderers
    PREFIX
        "Renderers"
    FILES
        Renderers/include/OpenGLRenderer.hpp
		Renderers/src/OpenGLRenderer.cpp
        Renderers/include/OpenGLRendererImpl.hpp
		Renderers/src/OpenGLRendererImpl.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Shaders
    PREFIX
        "Shaders"
    FILES
        Shaders/include/OpenGLShader.hpp
		Shaders/src/OpenGLShader.cpp
)

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

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Vertices
    PREFIX
        "Vertices"
    FILES
		Vertices/include/VertexAttributes.hpp
        Vertices/include/VertexLayouts.hpp
		Vertices/src/VertexLayouts.cpp
        Vertices/include/VertexLayoutsImpl.hpp
		Vertices/src/VertexLayoutsImpl.cpp
        Vertices/include/Vertex.hpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLLoader
    PREFIX
        "OpenGLLoader"
    FILES
        OpenGLLoader/include/OpenGLLoader.hpp
		OpenGLLoader/src/OpenGLLoader.cpp
        OpenGLLoader/include/OpenGLLoaderImpl.hpp
		OpenGLLoader/src/OpenGLLoaderImpl.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Attributes
    PREFIX
        "Attributes"
    FILES
        Attributes/include/Points.hpp
        Attributes/include/Colors.hpp
)