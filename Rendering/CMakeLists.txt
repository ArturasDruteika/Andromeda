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

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    Rendering/MacroExports/include/MacroExports.hpp
)

# ==== OpenGL backend (platform specific) ====
set(OPENGL_HEADERS
    Rendering/OpenGL/Geometry/include/GpuMeshOpenGL.hpp
    Rendering/OpenGL/Renderer/include/RendererOpenGLImpl.hpp
    Rendering/OpenGL/Support/include/FaceCullingControlOpenGL.hpp
    Rendering/OpenGL/Support/include/FrameBufferOpenGL.hpp
    Rendering/OpenGL/Support/include/MeshCacheOpenGL.hpp
    Rendering/OpenGL/Support/include/ShadowRendererOpenGL.hpp
    Rendering/OpenGL/Vertices/include/VertexLayoutOpenGL.hpp
)

set(OPENGL_SOURCES
    Rendering/OpenGL/Geometry/src/GpuMeshOpenGL.cpp
    Rendering/OpenGL/Renderer/src/RendererOpenGLImpl.cpp
    Rendering/OpenGL/Support/src/FaceCullingControlOpenGL.cpp
    Rendering/OpenGL/Support/src/FrameBufferOpenGL.cpp
    Rendering/OpenGL/Support/src/MeshCacheOpenGL.cpp
    Rendering/OpenGL/Support/src/ShadowRendererOpenGL.cpp
    Rendering/OpenGL/Vertices/src/VertexLayoutOpenGL.cpp
)

# ==== RayTracing ====
set(RAYTRACING_HEADERS
    Rendering/RayTracing/include/Ray.hpp
)

# ==== Renderers ====
set(RENDERERS_HEADERS
    Rendering/Renderers/Abstracts/include/GridControl.hpp
    Rendering/Renderers/Abstracts/include/IlluminationControl.hpp
    Rendering/Renderers/Abstracts/include/SizeControl.hpp
    Rendering/Renderers/Renderers/include/RendererOpenGL.hpp
)

set(RENDERERS_SOURCES
    Rendering/Renderers/Abstracts/src/GridControl.cpp
    Rendering/Renderers/Abstracts/src/IlluminationControl.cpp
    Rendering/Renderers/Abstracts/src/SizeControl.cpp
    Rendering/Renderers/Renderers/src/RendererOpenGL.cpp
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

# ==== Vertices (API agnostic) ====
set(VERTEX_HEADERS
    Rendering/Vertices/include/VertexFormat.hpp
    Rendering/Vertices/include/VertexAttributes.hpp
    Rendering/Vertices/include/VertexLayouts.hpp
    Rendering/Vertices/include/VertexLocationPolicy.hpp
)

set(VERTEX_SOURCES
    Rendering/Vertices/src/VertexFormat.cpp
    Rendering/Vertices/src/VertexLayouts.cpp
    Rendering/Vertices/src/VertexLocationPolicy.cpp
)

add_library(${PROJECT_NAME}
    SHARED
        ${MACRO_EXPORTS_HEADERS}
        ${RAYTRACING_HEADERS}
        ${RENDERERS_HEADERS}
        ${RENDERERS_SOURCES}
        ${SCENE_HEADERS}
        ${SCENE_SOURCES}
        ${SHADERS_HEADERS}
        ${SHADERS_SOURCES}
        ${UTILS_HEADERS}
        ${UTILS_SOURCES}
        ${VERTEX_HEADERS}
        ${VERTEX_SOURCES}
        ${OPENGL_HEADERS}
        ${OPENGL_SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# Link libraries - Api is INTERFACE, so this just pulls in its usage requirements
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
)

add_dependencies(${PROJECT_NAME}
    Utils
    Math
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
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/MacroExports
    PREFIX
        "MacroExports"
    FILES
        ${MACRO_EXPORTS_HEADERS}
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

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/OpenGL
    PREFIX
        "OpenGL"
    FILES
        ${OPENGL_HEADERS}
        ${OPENGL_SOURCES}
)
