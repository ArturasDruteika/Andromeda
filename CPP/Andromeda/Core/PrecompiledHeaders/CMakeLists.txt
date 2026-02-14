cmake_minimum_required(VERSION 3.24)

project(PrecompiledHeaders LANGUAGES CXX)

# Require C++23 for consumers
add_library(PrecompiledHeaders INTERFACE)
target_compile_features(PrecompiledHeaders INTERFACE cxx_std_23)

# Header location exported to consumers
target_include_directories(PrecompiledHeaders
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# The actual PCH (applies to any target that links this INTERFACE)
target_precompile_headers(PrecompiledHeaders
    INTERFACE
        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp>"
)

# (Optional) group for IDEs
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "PrecompiledHeaders" FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp
)
