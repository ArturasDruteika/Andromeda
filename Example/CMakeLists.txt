cmake_minimum_required(VERSION 3.24)

project(Example)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

# Ensure the include directories are properly formatted
include_directories(
    ..//Utils//PrecompiledHeaders//include//
    ../Math/LinearAlgebra/include/
    ../Space/Objects/include/
    ../Space/Scene/include/
    ../Space/Attributes/include/
    ../Space/DataTypes/include/
    ../Rendering/Scene/include/
    ../Rendering/RenderableObjects/include/
    ../EngineCore/Application/include/
)

# Ensure EngineCore is linked
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        Utils
        Math
        Space
        Rendering
        EngineCore
)

# Ensure Example waits for EngineCore to build
add_dependencies(${PROJECT_NAME} 
    Utils
    Math
    Space
    Rendering
    EngineCore
)

# Enable precompiled headers
target_precompile_headers(${PROJECT_NAME} 
    REUSE_FROM
        Utils
)

# Set working directory only for Visual Studio
if(MSVC)
    file(TO_CMAKE_PATH $<TARGET_FILE_DIR:${PROJECT_NAME}>// exe_dir)
    set_target_properties(${PROJECT_NAME} 
        PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY ${exe_dir}
    )
else()
    set_target_properties(${PROJECT_NAME} 
    PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin"
    )
endif()
