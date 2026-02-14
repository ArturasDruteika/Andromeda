cmake_minimum_required(VERSION 3.24)

project(Engine)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DENGINECORE_EXPORT)

# SPDLog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../3rdParty/spdlog/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../3rdParty/spdlog/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)


# ==== Engine ====
set(ENGINE_HEADERS
    Engine/Engine/include/Engine.hpp
)

set(ENGINE_SOURCES
    Engine/Engine/src/Engine.cpp
)

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    Engine/MacroExports/include/MacroExports.hpp
)

# ==== Target ====
add_library(${PROJECT_NAME}
    SHARED
        ${APPLICATION_HEADERS}
        ${APPLICATION_SOURCES}
        ${ENGINE_HEADERS}
        ${ENGINE_SOURCES}
        ${MACRO_EXPORTS_HEADERS}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE 
        ANDROMEDA_API_BUILD
)

# Link libraries (alphabetical)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Rendering
        spdlog::spdlog
    PUBLIC
        PrecompiledHeaders
        Math
        Api

)

# Explicit build ordering (alphabetical)
add_dependencies(${PROJECT_NAME}
    Math
    Rendering
    Utils
    Window
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
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        # Copy and rename directly to the SONAME the loader expects
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${spdlog_root_path}/bin/$<$<CONFIG:Debug>:libspdlogd.so.1.15.3>$<$<CONFIG:Release>:libspdlog.so.1.15.3>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/$<$<CONFIG:Debug>:libspdlogd.so.1.15>$<$<CONFIG:Release>:libspdlog.so.1.15>
    )
endif()

# ==== IDE Organization ====
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Engine
    PREFIX
        "Engine"
    FILES
        ${ENGINE_HEADERS}
        ${ENGINE_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/MacroExports
    PREFIX
        "MacroExports"
    FILES
        ${MACRO_EXPORTS_HEADERS}
)
