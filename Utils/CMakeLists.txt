cmake_minimum_required(VERSION 3.24)

project(Utils)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the Utils library target
add_library(${PROJECT_NAME} STATIC
	precompiled_headers/include/pch.hpp
	precompiled_headers/src/pch.cpp
)

# Add source files
target_sources(${PROJECT_NAME} PRIVATE
    precompiled_headers/src/pch.cpp
)

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC
    precompiled_headers/include
)

# Enable precompiled headers
target_precompile_headers(${PROJECT_NAME} PUBLIC
    precompiled_headers/include/pch.hpp
)
