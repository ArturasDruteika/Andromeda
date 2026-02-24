cmake_minimum_required(VERSION 3.24)

project(EarthRotatingAroundSun)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        ANDROMEDA_API_USE_DLL
)

# Ensure Engine is linked
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        # PrecompiledHeaders
        Math
        Api
        Space
        Platform
        Engine
        Application
        spdlog::spdlog
)

# Ensure Example waits for Engine to build
add_dependencies(${PROJECT_NAME}
    Math
    Space
    Platform
    Engine
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
