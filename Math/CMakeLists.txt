cmake_minimum_required(VERSION 3.24)

project(Math)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DMATH_EXPORT)

add_library(${PROJECT_NAME} 
    SHARED
        LinearAlgebra/include/LinearAlgebraDataTypes.hpp
        LinearAlgebra/include/LinearAlgebraOperations.hpp
        LinearAlgebra/src/LinearAlgebraOperations.cpp
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ..//Utils//PrecompiledHeaders//include//
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        Utils
)

add_dependencies(${PROJECT_NAME} 
    Utils
)

# Enable precompiled headers
target_precompile_headers(${PROJECT_NAME} 
    REUSE_FROM
        Utils
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra 
    PREFIX 
        "LinearAlgebra" 
    FILES
        LinearAlgebra/include/LinearAlgebraDataTypes.hpp
        LinearAlgebra/include/LinearAlgebraOperations.hpp
        LinearAlgebra/src/LinearAlgebraOperations.cpp
)