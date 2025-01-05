cmake_minimum_required(VERSION 3.24)

project(Utils)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SPDLog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

# Create a library target
add_library(${PROJECT_NAME} 
    STATIC
        precompiled_headers/src/pch.cpp
)

target_sources(${PROJECT_NAME}
    PRIVATE
        precompiled_headers/include/pch.hpp
        precompiled_headers/src/pch.cpp
)

# Link spdlog
target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        spdlog::spdlog
)

# Enable precompiled headers
target_precompile_headers(${PROJECT_NAME} 
    PUBLIC
        precompiled_headers/include/pch.hpp
)

# Organize files in Solution Explorer
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR} 
    FILES
        precompiled_headers/include/pch.hpp
        precompiled_headers/src/pch.cpp
)


### Post builds
# SPDLog
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD 
	COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different
    ${spdlog_root_path}//bin//$<$<CONFIG:debug>:spdlogd.dll>$<$<CONFIG:release>:spdlog.dll>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)