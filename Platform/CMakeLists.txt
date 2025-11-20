cmake_minimum_required(VERSION 3.24)

project(Platform)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenGL
find_package(OpenGL REQUIRED)

# SPDLog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

# ==== Platform ====
set(PLATFORM_HEADERS
    Platform/include/Platform.hpp
)

set(PLATFORM_SOURCES
    Platform/src/Platform.cpp
)

# ==== Target ====
add_library(${PROJECT_NAME}
    STATIC
        ${PLATFORM_HEADERS}
        ${PLATFORM_SOURCES}
)

# target_compile_definitions(${PROJECT_NAME}
#     PRIVATE
#         ANDROMEDA_PLATFORM_BUILD
# )

if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()

# Include dirs (alphabetical)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Platform/include
    PRIVATE
        ../Context/GLFWContext/include/
        ../Window/GLFWWindow/include/
        ../glfw/
        ../glfw/include/
        ../imgui/imgui/
        ../imgui/imgui/backends/
)

# Link libraries (alphabetical)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Context
        Glad
        OpenGL::GL
        Window
        glfw
        imgui
        spdlog::spdlog
    PUBLIC
        PrecompiledHeaders
)

# Explicit build ordering (alphabetical)
add_dependencies(${PROJECT_NAME}
    Context
    Glad
    Utils
    Window
    glfw
    imgui
)

### Post builds
# SPDLog
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_custom_command(
        TARGET 
            ${PROJECT_NAME} POST_BUILD 
        COMMAND 
            ${CMAKE_COMMAND} ARGS -E copy_if_different
            ${spdlog_root_path}//bin//$<$<CONFIG:debug>:spdlogd.dll>$<$<CONFIG:release>:spdlog.dll>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        # Copy and rename directly to the SONAME the loader expects
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${spdlog_root_path}/bin/$<$<CONFIG:Debug>:libspdlogd.so.1.15.3>$<$<CONFIG:Release>:libspdlog.so.1.15.3>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/$<$<CONFIG:Debug>:libspdlogd.so.1.15>$<$<CONFIG:Release>:libspdlog.so.1.15>
    )
endif()

# ==== IDE Organization ====
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Platform
    PREFIX
        "Platform"
    FILES
        ${PLATFORM_HEADERS}
        ${PLATFORM_SOURCES}
)
