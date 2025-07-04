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
        PrecompiledHeaders/include/pch.hpp
        PrecompiledHeaders/src/pch.cpp
        FileOperations/include/FileOperations.hpp
        FileOperations/src/FileOperations.cpp
        nlohmann_json/include/json.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Link spdlog
target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        spdlog::spdlog
)

# Enable precompiled headers
target_precompile_headers(${PROJECT_NAME} 
    PUBLIC
        PrecompiledHeaders/include/pch.hpp
)


### Post builds
# SPDLog
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if(MSVC)
        add_custom_command(
            TARGET 
                ${PROJECT_NAME} POST_BUILD 
            COMMAND 
                ${CMAKE_COMMAND} ARGS -E copy_if_different
                ${spdlog_root_path}//bin//$<$<CONFIG:debug>:spdlogd.dll>$<$<CONFIG:release>:spdlog.dll>
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    else()
        add_custom_command(
            TARGET 
                ${PROJECT_NAME} POST_BUILD 
            COMMAND 
                ${CMAKE_COMMAND} ARGS -E copy_if_different
                ${spdlog_root_path}//bin//$<$<CONFIG:debug>:spdlogd.dll>$<$<CONFIG:release>:spdlog.dll>
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endif()
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_custom_command(
        TARGET 
            ${PROJECT_NAME} POST_BUILD 
        COMMAND 
            ${CMAKE_COMMAND} ARGS -E copy_if_different
            ${spdlog_root_path}/bin/$<$<CONFIG:debug>:libspdlogd.so.1.15.1>$<$<CONFIG:release>:libspdlog.so.1.15.1>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()


# Organize files in Solution Explorer
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders
    PREFIX
        "PrecompiledHeaders"
    FILES
        PrecompiledHeaders/include/pch.hpp
        PrecompiledHeaders/src/pch.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/FileOperations
    PREFIX
        "FileOperations"
    FILES
        FileOperations/include/FileOperations.hpp
        FileOperations/src/FileOperations.cpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json
    PREFIX
        "nlohmann_json"
    FILES
        nlohmann_json/include/json.hpp
)