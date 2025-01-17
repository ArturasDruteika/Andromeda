cmake_minimum_required(VERSION 3.24.0)
project(ExternalGraphicsLibs)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find and configure OpenGL
find_package(OpenGL REQUIRED)

# # GLFW options
# set(GLFW_BUILD_DOCS OFF CACHE BOOL "Disable GLFW docs" FORCE)
# set(GLFW_BUILD_TESTS OFF CACHE BOOL "Disable GLFW tests" FORCE)
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Disable GLFW examples" FORCE)
# set(GLFW_INSTALL OFF CACHE BOOL "Disable GLFW install" FORCE)

# # Add GLFW source code
# add_subdirectory(glfw)

# Add GLAD source code
add_library(${PROJECT_NAME} 
    SHARED 
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/gl.c
)

# Define GLM_DLL_EXPORT for exporting symbols
target_compile_definitions(${PROJECT_NAME} 
    PRIVATE 
        GLAD_API_CALL_EXPORT_BUILD
    PUBLIC 
        GLAD_API_CALL_EXPORT
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        # glfw/include
        glad/include
	    glm/
        ${OPENGL_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        # glfw
        ${OPENGL_LIBRARIES}
)
