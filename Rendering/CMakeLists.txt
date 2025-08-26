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

# ==== Camera ====
set(CAMERA_HEADERS
    Camera/include/Camera.hpp
    Camera/include/CameraImpl.hpp
    Camera/include/ICamera.hpp
)

set(CAMERA_SOURCES
    Camera/src/Camera.cpp
    Camera/src/CameraImpl.cpp
    Camera/src/ICamera.cpp
)

# ==== Light ====
set(LIGHT_HEADERS
    Light/Abstracts/include/Light.hpp
    Light/Abstracts/include/LuminousBehavior.hpp
    Light/Abstracts/include/NonLuminousBehavior.hpp
    Light/Interfaces/include/ILightBehavior.hpp
    Light/LightTypes/include/DirectionalLight.hpp
    Light/LightTypes/include/PointLight.hpp
    Light/LightTypes/include/SpotLight.hpp
    Light/Support/include/LightData.hpp
    Light/Support/include/LightTypes.hpp
)

set(LIGHT_SOURCES
    Light/Abstracts/src/Light.cpp
    Light/Abstracts/src/LuminousBehavior.cpp
    Light/Abstracts/src/NonLuminousBehavior.cpp
    Light/Interfaces/src/ILightBehavior.cpp
    Light/LightTypes/src/DirectionalLight.cpp
    Light/LightTypes/src/PointLight.cpp
    Light/LightTypes/src/SpotLight.cpp
    Light/Support/src/LightData.cpp
)

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    MacroExports/include/MacroExports.hpp
)


# ==== Materials ====
set(MATERIALS_HEADERS
    Materials/include/Materials.hpp
    Materials/include/MaterialsLibrary.hpp
    Materials/include/MaterialTypes.hpp
)

set(MATERIALS_SOURCES
    Materials/src/Materials.cpp
    Materials/src/MaterialsLibrary.cpp
)

# ==== OpenGLLoader ====
set(LOADER_HEADERS
    OpenGLLoader/include/OpenGLLoader.hpp
    OpenGLLoader/include/OpenGLLoaderImpl.hpp
)

set(LOADER_SOURCES
    OpenGLLoader/src/OpenGLLoader.cpp
    OpenGLLoader/src/OpenGLLoaderImpl.cpp
)

# ==== RayTracing ====
set(RAYTRACING_HEADERS
    RayTracing/include/Ray.hpp
)

# ==== RenderableObjects ====
set(RO_HEADERS
    RenderableObjects/Abstracts/include/Geometry.hpp
    RenderableObjects/Abstracts/include/Luminous.hpp
    RenderableObjects/Abstracts/include/RenderableObject.hpp
    RenderableObjects/Abstracts/include/RenderableObjectOpenGL.hpp
    RenderableObjects/Abstracts/include/Transformable.hpp
    RenderableObjects/Interfaces/include/IGeometry.hpp
    RenderableObjects/Interfaces/include/ILuminous.hpp
    RenderableObjects/Interfaces/include/IRenderableObject.hpp
    RenderableObjects/Interfaces/include/IRenderableObjectOpenGL.hpp
    RenderableObjects/Interfaces/include/ITransformable.hpp
    RenderableObjects/Objects/include/CubeObjectOpenGL.hpp
    RenderableObjects/Objects/include/CubeObjectOpenGLImpl.hpp
    RenderableObjects/Objects/include/GridOpenGL.hpp
    RenderableObjects/Objects/include/SphereObjectOpenGL.hpp
    RenderableObjects/Objects/include/SphereObjectOpenGLImpl.hpp
    RenderableObjects/Support/include/TransformationTypes.hpp
)

set(RO_SOURCES
    RenderableObjects/Abstracts/src/Geometry.cpp
    RenderableObjects/Abstracts/src/Luminous.cpp
    RenderableObjects/Abstracts/src/RenderableObject.cpp
    RenderableObjects/Abstracts/src/RenderableObjectOpenGL.cpp
    RenderableObjects/Abstracts/src/Transformable.cpp
    RenderableObjects/Interfaces/src/IGeometry.cpp
    RenderableObjects/Interfaces/src/ILuminous.cpp
    RenderableObjects/Interfaces/src/IRenderableObject.cpp
    RenderableObjects/Interfaces/src/IRenderableObjectOpenGL.cpp
    RenderableObjects/Interfaces/src/ITransformable.cpp
    RenderableObjects/Objects/src/CubeObjectOpenGL.cpp
    RenderableObjects/Objects/src/CubeObjectOpenGLImpl.cpp
    RenderableObjects/Objects/src/GridOpenGL.cpp
    RenderableObjects/Objects/src/SphereObjectOpenGL.cpp
    RenderableObjects/Objects/src/SphereObjectOpenGLImpl.cpp
)

# ==== Renderers ====
set(RENDERERS_HEADERS
    Renderers/Abstracts/include/CameraControl.hpp
    Renderers/Abstracts/include/FaceCullingControlOpenGL.hpp
    Renderers/Abstracts/include/GridControl.hpp
    Renderers/Abstracts/include/IlluminationControl.hpp
    Renderers/Abstracts/include/Renderer.hpp
    Renderers/Abstracts/include/RendererOpenGL.hpp
    Renderers/Abstracts/include/SizeControl.hpp
    Renderers/Interfaces/include/ICameraControl.hpp
    Renderers/Interfaces/include/IFrameBufferProvider.hpp
    Renderers/Interfaces/include/IGridControl.hpp
    Renderers/Interfaces/include/IIlluminationControl.hpp
    Renderers/Interfaces/include/IRenderer.hpp
    Renderers/Interfaces/include/IRendererOpenGL.hpp
    Renderers/Interfaces/include/ISizeControl.hpp
    Renderers/Renderers/include/OpenGLRenderer.hpp
    Renderers/Renderers/include/OpenGLRendererImpl.hpp
    Renderers/Support/include/FrameBufferOpenGL.hpp
)

set(RENDERERS_SOURCES
    Renderers/Abstracts/src/CameraControl.cpp
    Renderers/Abstracts/src/FaceCullingControlOpenGL.cpp
    Renderers/Abstracts/src/GridControl.cpp
    Renderers/Abstracts/src/IlluminationControl.cpp
    Renderers/Abstracts/src/Renderer.cpp
    Renderers/Abstracts/src/RendererOpenGL.cpp
    Renderers/Abstracts/src/SizeControl.cpp
    Renderers/Interfaces/src/ICameraControl.cpp
    Renderers/Interfaces/src/IFrameBufferProvider.cpp
    Renderers/Interfaces/src/IGridControl.cpp
    Renderers/Interfaces/src/IIlluminationControl.cpp
    Renderers/Interfaces/src/IRenderer.cpp
    Renderers/Interfaces/src/IRendererOpenGL.cpp
    Renderers/Interfaces/src/ISizeControl.cpp
    Renderers/Renderers/src/OpenGLRenderer.cpp
    Renderers/Renderers/src/OpenGLRendererImpl.cpp
    Renderers/Support/src/FrameBufferOpenGL.cpp
)

# ==== Scene ====
set(SCENE_HEADERS
    Scene/Abstracts/include/Scene.hpp
    Scene/Abstracts/include/SceneEnvironment.hpp
    Scene/Abstracts/include/SceneLighting.hpp
    Scene/Abstracts/include/SceneObjects.hpp
    Scene/Abstracts/include/SceneState.hpp
    Scene/Interfaces/include/IScene.hpp
    Scene/Interfaces/include/ISceneEnvironment.hpp
    Scene/Interfaces/include/ISceneLighting.hpp
    Scene/Interfaces/include/ISceneObjects.hpp
    Scene/Interfaces/include/ISceneState.hpp
    Scene/Scenes/include/OpenGLScene.hpp
    Scene/Scenes/include/OpenGLSceneImpl.hpp
    Scene/Support/include/SpecialIndices.hpp
)

set(SCENE_SOURCES
    Scene/Abstracts/src/Scene.cpp
    Scene/Abstracts/src/SceneEnvironment.cpp
    Scene/Abstracts/src/SceneLighting.cpp
    Scene/Abstracts/src/SceneObjects.cpp
    Scene/Abstracts/src/SceneState.cpp
    Scene/Interfaces/src/IScene.cpp
    Scene/Interfaces/src/ISceneEnvironment.cpp
    Scene/Interfaces/src/ISceneLighting.cpp
    Scene/Interfaces/src/ISceneObjects.cpp
    Scene/Interfaces/src/ISceneState.cpp
    Scene/Scenes/src/OpenGLScene.cpp
    Scene/Scenes/src/OpenGLSceneImpl.cpp
)

# ==== Shaders ====
set(SHADERS_HEADERS
    Shaders/Abstracts/include/ShaderCompilerOpenGL.hpp
    Shaders/Abstracts/include/ShaderProgramOpenGL.hpp
    Shaders/Abstracts/include/ShaderSourceManagerOpenGL.hpp
    Shaders/Abstracts/include/UniformSetterOpenGL.hpp
    Shaders/Interfaces/include/IShader.hpp
    Shaders/Shaders/include/ShaderManager.hpp
    Shaders/Shaders/include/ShaderOpenGL.hpp
    Shaders/Support/include/ShaderOpenGLTypes.hpp
    Shaders/Support/include/ShaderTypes.hpp
)

set(SHADERS_SOURCES
    Shaders/Abstracts/src/ShaderCompilerOpenGL.cpp
    Shaders/Abstracts/src/ShaderProgramOpenGL.cpp
    Shaders/Abstracts/src/ShaderSourceManagerOpenGL.cpp
    Shaders/Abstracts/src/UniformSetterOpenGL.cpp
    Shaders/Interfaces/src/IShader.cpp
    Shaders/Shaders/src/ShaderManager.cpp
    Shaders/Shaders/src/ShaderOpenGL.cpp
)

# ==== Utilities ====
set(UTILS_HEADERS
    Utils/include/MathUtils.hpp
)

set(UTILS_SOURCES
    Utils/src/MathUtils.cpp
)

# ==== Vertices ====
set(VERTEX_HEADERS
    Vertices/include/VertexAttributes.hpp
    Vertices/include/VertexLayouts.hpp
    Vertices/include/Vertex.hpp
)

set(VERTEX_SOURCES
    Vertices/src/VertexLayouts.cpp
)

add_library(${PROJECT_NAME} 
    SHARED
        ${CAMERA_HEADERS}
        ${CAMERA_SOURCES}
        ${LIGHT_HEADERS}
        ${LIGHT_SOURCES}
        ${MACRO_EXPORTS_HEADERS}
        ${LOADER_HEADERS}
        ${LOADER_SOURCES}
        ${MATERIALS_HEADERS}
        ${MATERIALS_SOURCES}
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
    PRIVATE
        # ..//Utils//PrecompiledHeaders//include//
        ..//Utils//FileOperations//include//
        ..//Utils//nlohmann_json//include//
        ..//ExternalGraphicsLibs//glad//include//
	    ..//ExternalGraphicsLibs//glm//
    PUBLIC
        ..//Math//LinearAlgebra//include//
        ..//Math//Constants//include//
        ..//Space//DataTypes//include//
        ..//Space//Attributes//include//
        ..//Space//Vertices//include//
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        PrecompiledHeaders
        Utils
        ExternalGraphicsLibs
        Math
)

add_dependencies(${PROJECT_NAME} 
    Utils
    ExternalGraphicsLibs
    Math
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
    "fragment_grid.glsl"
    "fragment_luminous_objects.glsl"
    "fragment_non_luminous_objects.glsl"
    "vertex_depth_only.glsl"
    "fragment_depth_only.glsl"
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

## Material properties
set(MATERIAL_JSON_FILENAME "material_properties.json")
set(MATERIAL_JSON_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/MaterialProperties/${MATERIAL_JSON_FILENAME}"
)
set(MATERIAL_JSON_OUTPUT_DIR
    "${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/material_properties"
)
set(MATERIAL_JSON_OUTPUT
    "${MATERIAL_JSON_OUTPUT_DIR}/${MATERIAL_JSON_FILENAME}"
)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory
        "${MATERIAL_JSON_OUTPUT_DIR}"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MATERIAL_JSON_SOURCE}"
        "${MATERIAL_JSON_OUTPUT}"

    COMMENT "Copying ${MATERIAL_JSON_FILENAME} to ${MATERIAL_JSON_OUTPUT_DIR}"
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Camera
    PREFIX
        "Camera"
    FILES
        ${CAMERA_HEADERS}
        ${CAMERA_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Light
    PREFIX
        "Light"
    FILES
        ${LIGHT_HEADERS}
        ${LIGHT_SOURCES}
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
        ${CMAKE_CURRENT_SOURCE_DIR}/Materials
    PREFIX
        "Materials"
    FILES
        ${MATERIALS_HEADERS}
        ${MATERIALS_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLLoader
    PREFIX
        "OpenGLLoader"
    FILES
        ${LOADER_HEADERS}
        ${LOADER_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/RayTracing
    PREFIX
        "RayTracing"
    FILES
        ${RAYTRACING_HEADERS}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderableObjects
    PREFIX
        "RenderableObjects"
    FILES
        ${RO_HEADERS}
        ${RO_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Renderers
    PREFIX
        "Renderers"
    FILES
        ${RENDERERS_HEADERS}
        ${RENDERERS_SOURCES}
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

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Shaders
    PREFIX
        "Shaders"
    FILES
        ${SHADERS_HEADERS}
        ${SHADERS_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils
    PREFIX
        "Utils"
    FILES
        ${UTILS_HEADERS}
        ${UTILS_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Vertices
    PREFIX
        "Vertices"
    FILES
        ${VERTEX_HEADERS}
        ${VERTEX_SOURCES}
)
