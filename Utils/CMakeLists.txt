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
        FileOperations/include/FileOperations.hpp
        FileOperations/src/FileOperations.cpp
        nlohmann_json/include/json.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Link spdlog
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        PrecompiledHeaders
        spdlog::spdlog
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