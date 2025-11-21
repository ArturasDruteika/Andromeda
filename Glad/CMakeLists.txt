cmake_minimum_required(VERSION 3.24.0)

project(Glad LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add GLAD source code
add_library(${PROJECT_NAME} 
    SHARED 
        glad/include/glad/gl.h
        glad/src/gl.c
        glad/include/KHR/khrplatform.h
)

# Position independent code is implicitly ON for SHARED libs, but this is fine
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE 
        GLAD_API_CALL_EXPORT_BUILD
    PUBLIC 
        GLAD_API_CALL_EXPORT
)

# Optional: nice grouping in IDE
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/glad
    PREFIX
        "Glad"
    FILES
        glad/include/glad/gl.h
        glad/include/KHR/khrplatform.h
        glad/src/gl.c
)
