cmake_minimum_required(VERSION 3.24.0)
project(Andromeda)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set(CMAKE_ASSETS_OUTPUT_DIRECTORY  ${PROJECT_BINARY_DIR})  # All the files that are not compiled
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")  # Executables
    set(CMAKE_ASSETS_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin")  # All the files that are not compiled
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")  # Shared Libraries (.so, .dll)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")  # Static Libraries (.a, .lib)
endif()

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(CMAKE_BUILD_PARALLEL_LEVEL)

add_subdirectory(Utils)
add_subdirectory(SystemLauncher)
add_subdirectory(ExternalGraphicsLibs)
add_subdirectory(EngineCore)
add_subdirectory(Rendering)
add_subdirectory(Window)
add_subdirectory(Context)
add_subdirectory(glfw)
add_subdirectory(imgui)
