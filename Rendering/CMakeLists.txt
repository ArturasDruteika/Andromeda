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

# SPDLog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

# ==== Camera ====
set(CAMERA_HEADERS
    Rendering/Camera/Abstracts/include/PerspectiveControl.hpp
    Rendering/Camera/Abstracts/include/CameraView.hpp
    Rendering/Camera/Abstracts/include/CameraController.hpp
    Rendering/Camera/Cameras/include/Camera.hpp
    Rendering/Camera/Cameras/include/CameraImpl.hpp
)

set(CAMERA_SOURCES
    Rendering/Camera/Abstracts/src/PerspectiveControl.cpp
    Rendering/Camera/Abstracts/src/CameraView.cpp
    Rendering/Camera/Abstracts/src/CameraController.cpp
    Rendering/Camera/Cameras/src/Camera.cpp
    Rendering/Camera/Cameras/src/CameraImpl.cpp
)

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    Rendering/MacroExports/include/MacroExports.hpp
)

# ==== OpenGLLoader ====
set(LOADER_HEADERS
    Rendering/OpenGLLoader/include/OpenGLLoader.hpp
    Rendering/OpenGLLoader/include/OpenGLLoaderImpl.hpp
)

set(LOADER_SOURCES
    Rendering/OpenGLLoader/src/OpenGLLoader.cpp
    Rendering/OpenGLLoader/src/OpenGLLoaderImpl.cpp
)

# ==== RayTracing ====
set(RAYTRACING_HEADERS
    Rendering/RayTracing/include/Ray.hpp
)

# ==== RenderableObjects ====
set(RO_HEADERS
    Rendering/RenderableObjects/Abstracts/include/Luminous.hpp
    Rendering/RenderableObjects/Abstracts/include/Mesh.hpp
    Rendering/RenderableObjects/Abstracts/include/RenderableObject.hpp
    Rendering/RenderableObjects/Abstracts/include/RenderableObjectOpenGL.hpp
    Rendering/RenderableObjects/Abstracts/include/Transformable.hpp
    Rendering/RenderableObjects/Interfaces/include/IRenderableObjectOpenGL.hpp
    Rendering/RenderableObjects/Objects/include/CubeObjectOpenGL.hpp
    Rendering/RenderableObjects/Objects/include/CubeObjectOpenGLImpl.hpp
    Rendering/RenderableObjects/Objects/include/GridOpenGL.hpp
    Rendering/RenderableObjects/Objects/include/SkyroomOpenGL.hpp
    Rendering/RenderableObjects/Objects/include/SkyroomOpenGLImpl.hpp
    Rendering/RenderableObjects/Objects/include/SphereObjectOpenGL.hpp
    Rendering/RenderableObjects/Objects/include/SphereObjectOpenGLImpl.hpp
)

set(RO_SOURCES
    Rendering/RenderableObjects/Abstracts/src/Luminous.cpp
    Rendering/RenderableObjects/Abstracts/src/Mesh.cpp
    Rendering/RenderableObjects/Abstracts/src/RenderableObject.cpp
    Rendering/RenderableObjects/Abstracts/src/RenderableObjectOpenGL.cpp
    Rendering/RenderableObjects/Abstracts/src/Transformable.cpp
    Rendering/RenderableObjects/Interfaces/src/IRenderableObjectOpenGL.cpp
    Rendering/RenderableObjects/Objects/src/CubeObjectOpenGL.cpp
    Rendering/RenderableObjects/Objects/src/CubeObjectOpenGLImpl.cpp
    Rendering/RenderableObjects/Objects/src/GridOpenGL.cpp
    Rendering/RenderableObjects/Objects/src/SkyroomOpenGL.cpp
    Rendering/RenderableObjects/Objects/src/SkyroomOpenGLImpl.cpp
    Rendering/RenderableObjects/Objects/src/SphereObjectOpenGL.cpp
    Rendering/RenderableObjects/Objects/src/SphereObjectOpenGLImpl.cpp
)

# ==== Renderers ====
set(RENDERERS_HEADERS
    Rendering/Renderers/Abstracts/include/CameraControl.hpp
    Rendering/Renderers/Abstracts/include/FaceCullingControlOpenGL.hpp
    Rendering/Renderers/Abstracts/include/GridControl.hpp
    Rendering/Renderers/Abstracts/include/IlluminationControl.hpp
    Rendering/Renderers/Abstracts/include/Renderer.hpp
    Rendering/Renderers/Abstracts/include/SizeControl.hpp
    Rendering/Renderers/Interfaces/include/IFrameBufferProvider.hpp
    Rendering/Renderers/Interfaces/include/IRendererOpenGL.hpp
    Rendering/Renderers/Renderers/include/RendererOpenGL.hpp
    Rendering/Renderers/Renderers/include/RendererOpenGLImpl.hpp
    Rendering/Renderers/Support/include/FrameBufferOpenGL.hpp
)

set(RENDERERS_SOURCES
    Rendering/Renderers/Abstracts/src/CameraControl.cpp
    Rendering/Renderers/Abstracts/src/FaceCullingControlOpenGL.cpp
    Rendering/Renderers/Abstracts/src/GridControl.cpp
    Rendering/Renderers/Abstracts/src/IlluminationControl.cpp
    Rendering/Renderers/Abstracts/src/Renderer.cpp
    Rendering/Renderers/Abstracts/src/SizeControl.cpp
    Rendering/Renderers/Interfaces/src/IFrameBufferProvider.cpp
    Rendering/Renderers/Interfaces/src/IRendererOpenGL.cpp
    Rendering/Renderers/Renderers/src/RendererOpenGL.cpp
    Rendering/Renderers/Renderers/src/RendererOpenGLImpl.cpp
    Rendering/Renderers/Support/src/FrameBufferOpenGL.cpp
)

# ==== Scene ====
set(SCENE_HEADERS
    Rendering/Scene/Abstracts/include/Scene.hpp
    Rendering/Scene/Abstracts/include/SceneEnvironment.hpp
    Rendering/Scene/Abstracts/include/SceneLighting.hpp
    Rendering/Scene/Abstracts/include/SceneObjects.hpp
    Rendering/Scene/Abstracts/include/SceneState.hpp
    Rendering/Scene/Scenes/include/SceneOpenGL.hpp
    Rendering/Scene/Scenes/include/SceneOpenGLImpl.hpp
    Rendering/Scene/Support/include/SpecialIndices.hpp
)

set(SCENE_SOURCES
    Rendering/Scene/Abstracts/src/Scene.cpp
    Rendering/Scene/Abstracts/src/SceneEnvironment.cpp
    Rendering/Scene/Abstracts/src/SceneLighting.cpp
    Rendering/Scene/Abstracts/src/SceneObjects.cpp
    Rendering/Scene/Abstracts/src/SceneState.cpp
    Rendering/Scene/Scenes/src/SceneOpenGL.cpp
    Rendering/Scene/Scenes/src/SceneOpenGLImpl.cpp
)

# ==== Shaders ====
set(SHADERS_HEADERS
    Rendering/Shaders/Abstracts/include/ShaderProgramOpenGL.hpp
    Rendering/Shaders/Abstracts/include/ShaderSourceManagerOpenGL.hpp
    Rendering/Shaders/Interfaces/include/IShader.hpp
    Rendering/Shaders/Shaders/include/ShaderManager.hpp
    Rendering/Shaders/Shaders/include/ShaderOpenGL.hpp
    Rendering/Shaders/Support/include/ShaderCompilerOpenGL.hpp
    Rendering/Shaders/Support/include/ShaderOpenGLTypes.hpp
    Rendering/Shaders/Support/include/ShaderTypes.hpp
    Rendering/Shaders/Support/include/UniformSetterOpenGL.hpp
)

set(SHADERS_SOURCES
    Rendering/Shaders/Abstracts/src/ShaderProgramOpenGL.cpp
    Rendering/Shaders/Abstracts/src/ShaderSourceManagerOpenGL.cpp
    Rendering/Shaders/Interfaces/src/IShader.cpp
    Rendering/Shaders/Shaders/src/ShaderManager.cpp
    Rendering/Shaders/Shaders/src/ShaderOpenGL.cpp
    Rendering/Shaders/Support/src/ShaderCompilerOpenGL.cpp
    Rendering/Shaders/Support/src/UniformSetterOpenGL.cpp
)

# ==== Utilities ====
set(UTILS_HEADERS
    Rendering/Utils/include/MathUtils.hpp
)

set(UTILS_SOURCES
    Rendering/Utils/src/MathUtils.cpp
)

# ==== Vertices ====
set(VERTEX_HEADERS
    Rendering/Vertices/include/VertexAttributes.hpp
    Rendering/Vertices/include/VertexLayouts.hpp
)

set(VERTEX_SOURCES
    Rendering/Vertices/src/VertexLayouts.cpp
)

add_library(${PROJECT_NAME} 
    SHARED
        ${CAMERA_HEADERS}
        ${CAMERA_SOURCES}
        ${MACRO_EXPORTS_HEADERS}
        ${LOADER_HEADERS}
        ${LOADER_SOURCES}
        ${RAYTRACING_HEADERS}
        ${RENDERERS_HEADERS}
        ${RENDERERS_SOURCES}
        ${RO_HEADERS}
        ${RO_SOURCES}
        ${SCENE_HEADERS}
        ${SCENE_SOURCES}
        ${SHADERS_HEADERS}
        ${SHADERS_SOURCES}
        ${UTILS_HEADERS}
        ${UTILS_SOURCES}
        ${VERTEX_HEADERS}
        ${VERTEX_SOURCES}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# Link libraries � Api is INTERFACE, so this just pulls in its usage requirements
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        PrecompiledHeaders
        Utils
        Glad
        spdlog::spdlog
        glm::glm
    PUBLIC
        Math
        Api
        Space
)

add_dependencies(${PROJECT_NAME}
    Utils
    Math
    Space
    Glad
)


### Post builds

## Shaders
# Define filenames
# Define shader filenames
set(SHADER_FILES
    "vertex.glsl"
    "fragment.glsl"
    "vertex_illumination.glsl"
    "vertex_grid.glsl"
    "vertex_point_shadow.glsl"
    "fragment_grid.glsl"
    "fragment_luminous_objects.glsl"
    "fragment_non_luminous_objects.glsl"
    "vertex_depth_only.glsl"
    "fragment_depth_only.glsl"
    "fragment_point_shadow.glsl"
    "geometry_point_shadow.glsl"
)

# Create full source paths
set(SHADER_SOURCE_PATHS "")
foreach(FILE_NAME IN LISTS SHADER_FILES)
    list(APPEND SHADER_SOURCE_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgramSources/${FILE_NAME}")
endforeach()

# Determine output directory based on platform
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SHADER_OUTPUT_DIR "${CMAKE_ASSETS_OUTPUT_DIRECTORY}/$<CONFIG>/shader_program_sources")
else()
    set(SHADER_OUTPUT_DIR "${CMAKE_ASSETS_OUTPUT_DIRECTORY}/shader_program_sources")
endif()

# Create output directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Creating directory ${SHADER_OUTPUT_DIR} for shaders"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADER_OUTPUT_DIR}"
)

# Copy shaders with echo for each
foreach(SHADER_PATH IN LISTS SHADER_SOURCE_PATHS) 
    get_filename_component(FILE_NAME "${SHADER_PATH}" NAME)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying ${FILE_NAME} to ${SHADER_OUTPUT_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SHADER_PATH}" "${SHADER_OUTPUT_DIR}/${FILE_NAME}"
    )
endforeach()

# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Camera
    PREFIX
        "Camera"
    FILES
        ${CAMERA_HEADERS}
        ${CAMERA_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/MacroExports
    PREFIX
        "MacroExports"
    FILES
        ${MACRO_EXPORTS_HEADERS}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/OpenGLLoader
    PREFIX
        "OpenGLLoader"
    FILES
        ${LOADER_HEADERS}
        ${LOADER_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/RayTracing
    PREFIX
        "RayTracing"
    FILES
        ${RAYTRACING_HEADERS}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/RenderableObjects
    PREFIX
        "RenderableObjects"
    FILES
        ${RO_HEADERS}
        ${RO_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Renderers
    PREFIX
        "Renderers"
    FILES
        ${RENDERERS_HEADERS}
        ${RENDERERS_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Scene
    PREFIX
        "Scene"
    FILES
        ${SCENE_HEADERS}
        ${SCENE_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Shaders
    PREFIX
        "Shaders"
    FILES
        ${SHADERS_HEADERS}
        ${SHADERS_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Utils
    PREFIX
        "Utils"
    FILES
        ${UTILS_HEADERS}
        ${UTILS_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Vertices
    PREFIX
        "Vertices"
    FILES
        ${VERTEX_HEADERS}
        ${VERTEX_SOURCES}
)
