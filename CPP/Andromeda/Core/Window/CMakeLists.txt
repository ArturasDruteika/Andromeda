cmake_minimum_required(VERSION 3.24)

project(Window)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${EXEC_NAME} OpenGL::GL)
if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${EXEC_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()

# SPDLog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../3rdParty/spdlog/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../3rdParty/spdlog/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

# ==== Events ====
set(EVENTS_HEADERS
    Window/Events/include/EventBase.hpp
    Window/Events/include/MouseEvents.hpp
    Window/Events/include/KeyEvents.hpp
    Window/Events/include/FrameBufferEvents.hpp
    Window/Events/include/EventDispatcher.hpp
)

set(EVENTS_SOURCES
    Window/Events/src/EventBase.cpp
    Window/Events/src/MouseEvents.cpp
    Window/Events/src/FrameBufferEvents.cpp
    Window/Events/src/KeyEvents.cpp
    Window/Events/src/EventDispatcher.cpp
)

# ==== WindowGLFW ====
set(WINDOW_GLFW_HEADERS
    Window/WindowGLFW/include/WindowGLFW.hpp
)

set(WINDOW_GLFW_SOURCES
    Window/WindowGLFW/src/WindowGLFW.cpp
)

add_library(${PROJECT_NAME} 
    STATIC
        ${EVENTS_HEADERS}
        ${EVENTS_SOURCES}
        ${WINDOW_GLFW_HEADERS}
        ${WINDOW_GLFW_SOURCES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        PrecompiledHeaders
        Utils
        glfw
        OpenGL::GL
        spdlog::spdlog
    PUBLIC
        Api
)

add_dependencies(${PROJECT_NAME} 
    Utils
    glfw
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Events 
    PREFIX 
        "Events" 
    FILES
        ${EVENTS_HEADERS}
        ${EVENTS_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/WindowGLFW 
    PREFIX 
        "WindowGLFW" 
    FILES
        ${WINDOW_GLFW_HEADERS}
        ${WINDOW_GLFW_SOURCES}
)
