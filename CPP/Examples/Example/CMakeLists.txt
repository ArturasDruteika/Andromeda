cmake_minimum_required(VERSION 3.24)

project(Example)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_definitions(Example 
    PRIVATE 
        ANDROMEDA_API_USE_DLL
)

# SPDLog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

# Ensure EngineCore is linked
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        # PrecompiledHeaders
        Math
        Api
        Space
        Platform
        EngineCore
        Application
        spdlog::spdlog
)

# Ensure Example waits for EngineCore to build
add_dependencies(${PROJECT_NAME} 
    Math
    Space
    Platform
    EngineCore
    Application
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
