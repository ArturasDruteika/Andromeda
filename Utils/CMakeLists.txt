cmake_minimum_required(VERSION 3.24)

project(Utils)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# spdlog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

# Create a library target (or executable target if needed)
add_library(${PROJECT_NAME} 
	STATIC
		# Add your source files here
		precompiled_headers/src/pch.cpp
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PUBLIC
	    spdlog::spdlog
)

# Enable precompiled headers
target_precompile_headers(${PROJECT_NAME} 
    PUBLIC
        precompiled_headers/include/pch.hpp
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR} 
    FILES
        precompiled_headers/include/pch.hpp
        precompiled_headers/src/pch.cpp
)
