cmake_minimum_required(VERSION 3.24)
project(Api LANGUAGES CXX)

add_library(Api STATIC)
set_target_properties(Api PROPERTIES LINKER_LANGUAGE CXX)  # <-- key line
target_compile_features(Api PUBLIC cxx_std_23)

# ==== Camera ====
set(CAMERA_HEADERS
    Camera/ICamera.hpp
    Camera/IPerspectiveControl.hpp
    Camera/ICameraView.hpp
    Camera/ICameraController.hpp
)

# ==== Engine ====
set(ENGINE_HEADERS
    Engine/IEngine.hpp
    Engine/GraphicsBackend.hpp
)

# ==== Renderer ====
set(RENDERER_HEADERS
    Renderer/ICameraControl.hpp
    Renderer/IGridControl.hpp
    Renderer/IIlluminationControl.hpp
    Renderer/IRenderer.hpp
    Renderer/ISizeControl.hpp
)

# ==== Scene ====
set(SCENE_HEADERS
    Scene/IScene.hpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/${CAMERA_HEADERS}
            ${CMAKE_CURRENT_SOURCE_DIR}/${ENGINE_HEADERS}
            ${CMAKE_CURRENT_SOURCE_DIR}/${RENDERER_HEADERS}
            ${CMAKE_CURRENT_SOURCE_DIR}/${SCENE_HEADERS}
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        PrecompiledHeaders
        Math
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
        ..//Math//LinearAlgebra//include//
)

add_dependencies(${PROJECT_NAME} 
    Math
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}  EXPORT ApiTargets FILE_SET HEADERS)
install(EXPORT ApiTargets NAMESPACE Andromeda:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME} )
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Camera 
    PREFIX 
        "Camera" 
    FILES
        ${CAMERA_HEADERS}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine 
    PREFIX 
        "Engine" 
    FILES
        ${ENGINE_HEADERS}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Renderer 
    PREFIX 
        "Renderer" 
    FILES
        ${RENDERER_HEADERS}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Scene 
    PREFIX 
        "Scene" 
    FILES
        ${SCENE_HEADERS}
)