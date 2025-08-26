cmake_minimum_required(VERSION 3.24)

project(Math)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DMATH_EXPORT)


# ==== Constants ====
set(CONSTANTS_HEADERS
    Constants/include/Constants.hpp
)

# ==== Linear Algebra ====
set(LINEAR_ALGEBRA_HEADERS
    LinearAlgebra/include/LinearAlgebraDataTypes.hpp
    LinearAlgebra/include/LinearAlgebraOperations.hpp
)

set(LINEAR_ALGEBRA_SOURCES
    LinearAlgebra/src/LinearAlgebraOperations.cpp
)

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    MacroExports/include/MacroExports.hpp
)

# ==== Trigonometry ====
set(TRIGONOMETRY_HEADERS
    Trigonometry/include/Trigonometry.hpp
)

set(TRIGONOMETRY_SOURCES
    Trigonometry/src/Trigonometry.cpp
)


# ==== Target ====
add_library(${PROJECT_NAME}
    SHARED
        ${CONSTANTS_HEADERS}
        ${LINEAR_ALGEBRA_HEADERS}
        ${LINEAR_ALGEBRA_SOURCES}
        ${MACRO_EXPORTS_HEADERS}
        ${TRIGONOMETRY_HEADERS}
        ${TRIGONOMETRY_SOURCES}
)

# ==== Link Libraries ====
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        PrecompiledHeaders
)


# ==== IDE Organization ====
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Constants
    PREFIX
        "Constants"
    FILES
        ${CONSTANTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra
    PREFIX
        "LinearAlgebra"
    FILES
        ${LINEAR_ALGEBRA_HEADERS}
        ${LINEAR_ALGEBRA_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/MacroExports
    PREFIX
        "MacroExports"
    FILES
        ${MACRO_EXPORTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Trigonometry
    PREFIX
        "Trigonometry"
    FILES
        ${TRIGONOMETRY_HEADERS}
        ${TRIGONOMETRY_SOURCES}
)
