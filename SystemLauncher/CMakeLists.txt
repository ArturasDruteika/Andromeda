cmake_minimum_required(VERSION 3.24)

project(SystemLauncher)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

# Ensure the include directories are properly formatted
include_directories(
    ../EngineCore/Application/include/
)

# Ensure EngineCore is linked
target_link_libraries(${PROJECT_NAME} PRIVATE EngineCore)

# Ensure SystemLauncher waits for EngineCore to build
add_dependencies(${PROJECT_NAME} EngineCore)

# Ensure OpenGL is properly found
find_package(OpenGL REQUIRED)

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
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()
