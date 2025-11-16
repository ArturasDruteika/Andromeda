cmake_minimum_required(VERSION 3.24.0)
project(Andromeda)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set(CMAKE_ASSETS_OUTPUT_DIRECTORY  ${PROJECT_BINARY_DIR})  # All the files that are not compiled
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")  # Executables
    set(CMAKE_ASSETS_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")  # All the files that are not compiled
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")  # Shared Libraries (.so, .dll)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")  # Static Libraries (.a, .lib)
endif()

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(CMAKE_BUILD_PARALLEL_LEVEL)

add_subdirectory(PrecompiledHeaders)
add_subdirectory(Api)
add_subdirectory(Math)
add_subdirectory(Utils)
add_subdirectory(PhysicalProperties)
add_subdirectory(glfw)
add_subdirectory(ExternalGraphicsLibs)
add_subdirectory(EngineCore)
add_subdirectory(Rendering)
add_subdirectory(Window)
add_subdirectory(Context)
add_subdirectory(imgui)
add_subdirectory(Example)

# --- Install Rules ---
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/INSTALL" CACHE PATH "Installation directory" FORCE)

# Install compiled binaries, excluding certain files
install(
    DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/" 
    DESTINATION "${CMAKE_INSTALL_PREFIX}/$<CONFIG>/"
    FILES_MATCHING
    PATTERN "*"
    PATTERN "*.lib" EXCLUDE
    PATTERN "*.exp" EXCLUDE
    PATTERN "*.pdb" EXCLUDE
)
