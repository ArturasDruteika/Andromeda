cmake_minimum_required(VERSION 3.24)

project(Example)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_definitions(Example 
    PRIVATE 
        ANDROMEDA_ENGINECORE_USE_DLL
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
	    # ../ExternalGraphicsLibs/glm/
        ../Math/LinearAlgebra/include/
        ../PhysicalProperties/Space/include/
        ../PhysicalProperties/Light/LightTypes/include/
        ../PhysicalProperties/Light/Abstracts/include/
        ../PhysicalProperties/Materials/include/
        # ../Rendering/RenderableObjects/Interfaces/include/
        # ../Rendering/RenderableObjects/Objects/include/
        ../Api/Engine/
)

# Ensure EngineCore is linked
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        # PrecompiledHeaders
        Math
        Api
        PhysicalProperties
        # Rendering
        EngineCore
)

# Ensure Example waits for EngineCore to build
add_dependencies(${PROJECT_NAME} 
    Math
    PhysicalProperties
    # ExternalGraphicsLibs
    # Rendering
    EngineCore
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
