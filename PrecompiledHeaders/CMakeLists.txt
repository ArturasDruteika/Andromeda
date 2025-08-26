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

# ---- spdlog integration (header-only preferred) ----
# If you still need your custom spdlog_DIR, keep these lines; otherwise remove them
# and rely on system-wide find_package(spdlog).
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

# Prefer header-only to avoid forcing link deps on consumers.
if (TARGET spdlog::spdlog_header_only)
    target_link_libraries(PrecompiledHeaders INTERFACE spdlog::spdlog_header_only)
else()
    target_link_libraries(PrecompiledHeaders INTERFACE spdlog::spdlog)
endif()

# (Optional) group for IDEs
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "PrecompiledHeaders" FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp
)
