cmake_minimum_required(VERSION 3.24.0)
project(ExternalGraphicsLibs)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find and configure OpenGL
find_package(OpenGL REQUIRED)

# Add GLAD source code
add_library(${PROJECT_NAME} 
    STATIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/glad/gl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/gl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/KHR/khrplatform.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        glad/include
	    glm/
        ${OPENGL_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        ${OPENGL_LIBRARIES}
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/glad
    PREFIX 
        "glad"
    FILES
        glad/include/glad/gl.h
        glad/include/KHR/khrplatform.h
        glad/src/gl.c
)
