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
        Renderers/include/FrameBufferOpenGL.hpp
		Renderers/src/FrameBufferOpenGL.cpp
        Renderers/include/IRenderer.hpp
        Renderers/src/IRenderer.cpp
        Renderers/include/IGridControl.hpp
        Renderers/src/IGridControl.cpp
        Renderers/include/IIlluminationControl.hpp
        Renderers/src/IIlluminationControl.cpp

        Shaders/include/OpenGLShader.hpp
		Shaders/src/OpenGLShader.cpp
		Shaders/include/ShaderOpenGLTypes.hpp
        Shaders/include/ShaderManager.hpp
		Shaders/src/ShaderManager.cpp

        Scene/include/OpenGLScene.hpp
		Scene/src/OpenGLScene.cpp
        Scene/include/OpenGLSceneImpl.hpp
		Scene/src/OpenGLSceneImpl.cpp
        Scene/include/SpecialIndices.hpp
        Scene/include/IScene.hpp
		Scene/src/IScene.cpp
        Scene/include/ISceneObjects.hpp
		Scene/src/ISceneObjects.cpp
        Scene/include/ISceneLighting.hpp
		Scene/src/ISceneLighting.cpp
        Scene/include/ISceneEnvironment.hpp
		Scene/src/ISceneEnvironment.cpp
        Scene/include/ISceneState.hpp
		Scene/src/ISceneState.cpp

        RenderableObjects/Abstracts/include/Geometry.hpp
		RenderableObjects/Abstracts/src/Geometry.cpp
        RenderableObjects/Abstracts/include/Luminous.hpp
		RenderableObjects/Abstracts/src/Luminous.cpp
        RenderableObjects/Abstracts/include/Transformable.hpp
		RenderableObjects/Abstracts/src/Transformable.cpp
        RenderableObjects/Abstracts/include/RenderableObject.hpp
		RenderableObjects/Abstracts/src/RenderableObject.cpp
        RenderableObjects/Abstracts/include/RenderableObjectOpenGL.hpp
		RenderableObjects/Abstracts/src/RenderableObjectOpenGL.cpp
        RenderableObjects/Interfaces/include/IGeometry.hpp
		RenderableObjects/Interfaces/src/IGeometry.cpp
        RenderableObjects/Interfaces/include/ILuminous.hpp
		RenderableObjects/Interfaces/src/ILuminous.cpp
        RenderableObjects/Interfaces/include/ITransformable.hpp
		RenderableObjects/Interfaces/src/ITransformable.cpp
        RenderableObjects/Interfaces/include/IRenderableObject.hpp
		RenderableObjects/Interfaces/src/IRenderableObject.cpp
        RenderableObjects/Interfaces/include/IRenderableObjectOpenGL.hpp
		RenderableObjects/Interfaces/src/IRenderableObjectOpenGL.cpp
        RenderableObjects/Objects/include/CubeObjectOpenGL.hpp
		RenderableObjects/Objects/src/CubeObjectOpenGL.cpp
        RenderableObjects/Objects/include/CubeObjectOpenGLImpl.hpp
		RenderableObjects/Objects/src/CubeObjectOpenGLImpl.cpp
		RenderableObjects/Objects/include/GridOpenGL.hpp
        RenderableObjects/Objects/src/GridOpenGL.cpp
        RenderableObjects/Objects/include/SphereObjectOpenGL.hpp
		RenderableObjects/Objects/src/SphereObjectOpenGL.cpp
        RenderableObjects/Objects/include/SphereObjectOpenGLImpl.hpp
		RenderableObjects/Objects/src/SphereObjectOpenGLImpl.cpp
		RenderableObjects/Support/include/TransformationTypes.hpp

		Vertices/include/VertexAttributes.hpp
        Vertices/include/VertexLayouts.hpp
		Vertices/src/VertexLayouts.cpp
		Vertices/include/Vertex.hpp

        OpenGLLoader/include/OpenGLLoader.hpp
		OpenGLLoader/src/OpenGLLoader.cpp
        OpenGLLoader/include/OpenGLLoaderImpl.hpp
		OpenGLLoader/src/OpenGLLoaderImpl.cpp
        
        Utils/include/MathUtils.hpp
		Utils/src/MathUtils.cpp

        Camera/include/Camera.hpp
		Camera/src/Camera.cpp
        Camera/include/CameraImpl.hpp
		Camera/src/CameraImpl.cpp

        Light/include/ILightBehavior.hpp
		Light/src/ILightBehavior.cpp
        Light/include/LuminousBehavior.hpp
		Light/src/LuminousBehavior.cpp
        Light/include/NonLuminousBehavior.hpp
		Light/src/NonLuminousBehavior.cpp
        Light/include/LightProperties.hpp
        Light/include/LightData.hpp
		Light/src/LightData.cpp
        Light/include/DirectionalLight.hpp
        Light/src/DirectionalLight.cpp
        Light/include/SpotLight.hpp
        Light/src/SpotLight.cpp
        Light/include/PointLight.hpp
        Light/src/PointLight.cpp
        Light/include/Light.hpp
        Light/src/Light.cpp

        RayTracing/include/Ray.hpp

        Materials/include/Materials.hpp
        Materials/src/Materials.cpp
        Materials/include/MaterialsLibrary.hpp
        Materials/src/MaterialsLibrary.cpp
        Materials/include/MaterialTypes.hpp
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ..//Utils//PrecompiledHeaders//include//
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
        Utils
        ExternalGraphicsLibs
        Math
)

add_dependencies(${PROJECT_NAME} 
    Utils
    ExternalGraphicsLibs
    Math
)

# Enable precompiled headers
target_precompile_headers(${PROJECT_NAME} 
    REUSE_FROM
        Utils
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
        ${CMAKE_CURRENT_SOURCE_DIR}/Renderers
    PREFIX
        "Renderers"
    FILES
        Renderers/include/OpenGLRenderer.hpp
		Renderers/src/OpenGLRenderer.cpp
        Renderers/include/OpenGLRendererImpl.hpp
		Renderers/src/OpenGLRendererImpl.cpp
        Renderers/include/FrameBufferOpenGL.hpp
		Renderers/src/FrameBufferOpenGL.cpp
        Renderers/include/IRenderer.hpp
        Renderers/src/IRenderer.cpp
        Renderers/include/IGridControl.hpp
        Renderers/src/IGridControl.cpp
        Renderers/include/IIlluminationControl.hpp
        Renderers/src/IIlluminationControl.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Shaders
    PREFIX
        "Shaders"
    FILES
        Shaders/include/OpenGLShader.hpp
		Shaders/src/OpenGLShader.cpp
        Shaders/include/ShaderOpenGLTypes.hpp
        Shaders/include/ShaderManager.hpp
		Shaders/src/ShaderManager.cpp
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
        Scene/include/SpecialIndices.hpp
        Scene/include/IScene.hpp
		Scene/src/IScene.cpp
        Scene/include/ISceneObjects.hpp
		Scene/src/ISceneObjects.cpp
        Scene/include/ISceneLighting.hpp
		Scene/src/ISceneLighting.cpp
        Scene/include/ISceneEnvironment.hpp
		Scene/src/ISceneEnvironment.cpp
        Scene/include/ISceneState.hpp
		Scene/src/ISceneState.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderableObjects
    PREFIX
        "RenderableObjects"
    FILES
        RenderableObjects/Abstracts/include/Geometry.hpp
        RenderableObjects/Abstracts/src/Geometry.cpp
        RenderableObjects/Abstracts/include/Luminous.hpp
        RenderableObjects/Abstracts/src/Luminous.cpp
        RenderableObjects/Abstracts/include/Transformable.hpp
        RenderableObjects/Abstracts/src/Transformable.cpp
        RenderableObjects/Abstracts/include/RenderableObject.hpp
        RenderableObjects/Abstracts/src/RenderableObject.cpp
        RenderableObjects/Abstracts/include/RenderableObjectOpenGL.hpp
        RenderableObjects/Abstracts/src/RenderableObjectOpenGL.cpp

        RenderableObjects/Interfaces/include/IGeometry.hpp
        RenderableObjects/Interfaces/src/IGeometry.cpp
        RenderableObjects/Interfaces/include/ILuminous.hpp
        RenderableObjects/Interfaces/src/ILuminous.cpp
        RenderableObjects/Interfaces/include/ITransformable.hpp
        RenderableObjects/Interfaces/src/ITransformable.cpp
        RenderableObjects/Interfaces/include/IRenderableObject.hpp
        RenderableObjects/Interfaces/src/IRenderableObject.cpp
        RenderableObjects/Interfaces/include/IRenderableObjectOpenGL.hpp
        RenderableObjects/Interfaces/src/IRenderableObjectOpenGL.cpp

        RenderableObjects/Objects/include/CubeObjectOpenGL.hpp
        RenderableObjects/Objects/src/CubeObjectOpenGL.cpp
        RenderableObjects/Objects/include/CubeObjectOpenGLImpl.hpp
        RenderableObjects/Objects/src/CubeObjectOpenGLImpl.cpp
        RenderableObjects/Objects/include/GridOpenGL.hpp
        RenderableObjects/Objects/src/GridOpenGL.cpp
        RenderableObjects/Objects/include/SphereObjectOpenGL.hpp
        RenderableObjects/Objects/src/SphereObjectOpenGL.cpp
        RenderableObjects/Objects/include/SphereObjectOpenGLImpl.hpp
        RenderableObjects/Objects/src/SphereObjectOpenGLImpl.cpp

        RenderableObjects/Support/include/TransformationTypes.hpp
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
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils
    PREFIX
        "Utils"
    FILES
        Utils/include/MathUtils.hpp
		Utils/src/MathUtils.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Camera
    PREFIX
        "Camera"
    FILES
        Camera/include/Camera.hpp
		Camera/src/Camera.cpp
        Camera/include/CameraImpl.hpp
		Camera/src/CameraImpl.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Light
    PREFIX
        "Light"
    FILES
        Light/include/ILightBehavior.hpp
		Light/src/ILightBehavior.cpp
        Light/include/LuminousBehavior.hpp
		Light/src/LuminousBehavior.cpp
        Light/include/NonLuminousBehavior.hpp
		Light/src/NonLuminousBehavior.cpp
        Light/include/LightProperties.hpp
        Light/include/LightData.hpp
		Light/src/LightData.cpp
        Light/include/DirectionalLight.hpp
        Light/src/DirectionalLight.cpp
        Light/include/SpotLight.hpp
        Light/src/SpotLight.cpp
        Light/include/PointLight.hpp
        Light/src/PointLight.cpp
        Light/include/Light.hpp
        Light/src/Light.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/RayTracing
    PREFIX
        "RayTracing"
    FILES
        RayTracing/include/Ray.hpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Materials
    PREFIX
        "Materials"
    FILES
        Materials/include/Materials.hpp
        Materials/src/Materials.cpp
        Materials/include/MaterialsLibrary.hpp
        Materials/src/MaterialsLibrary.cpp
        Materials/include/MaterialTypes.hpp
)