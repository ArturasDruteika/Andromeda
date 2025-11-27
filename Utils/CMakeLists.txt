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


# ==== FileOperations ====
set(FILE_OPERATIONS_HEADERS
    Utils/FileOperations/include/FileOperations.hpp
)

set(FILE_OPERATIONS_SOURCES
    Utils/FileOperations/src/FileOperations.cpp
)

# ==== nlohmann ====
set(NLOHMANN_HEADERS
    Utils/nlohmann_json/include/json.hpp
)


# Create a library target
add_library(${PROJECT_NAME} 
    STATIC
        ${FILE_OPERATIONS_HEADERS}
        ${FILE_OPERATIONS_SOURCES}
        ${NLOHMANN_HEADERS}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
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
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/FileOperations
    PREFIX
        "FileOperations"
    FILES
        ${FILE_OPERATIONS_HEADERS}
        ${FILE_OPERATIONS_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/nlohmann_json
    PREFIX
        "nlohmann_json"
    FILES
        ${NLOHMANN_HEADERS}
)