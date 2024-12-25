cmake_minimum_required(VERSION 3.24.0)
project(ExternalGraphicsLibs)

# Compiler-specific settings
if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

# Find and configure OpenGL
find_package(OpenGL REQUIRED)

# GLFW options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Disable GLFW docs" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Disable GLFW tests" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Disable GLFW examples" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "Disable GLFW install" FORCE)

# Add GLFW source code
add_subdirectory(glfw)

# Add GLAD source code
add_library(GLAD STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/gl.c
)

# Specify GLAD include directory explicitly
target_include_directories(GLAD PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

# Link GLAD with OpenGL
target_link_libraries(GLAD PUBLIC OpenGL::GL)

# Combine GLFW and GLAD into ExternalGraphicsLibs
add_library(ExternalGraphicsLibs INTERFACE)

# Include GLFW and GLAD headers for the combined library
# INTERFACE target ensures headers are passed to dependent targets
target_include_directories(ExternalGraphicsLibs INTERFACE
    glfw/include
    glad/include
	glm/
)

# Link GLFW, GLAD, and OpenGL into ExternalGraphicsLibs
# INTERFACE target ensures libraries are passed to dependent targets
target_link_libraries(ExternalGraphicsLibs INTERFACE
    glfw
    GLAD
    OpenGL::GL
)
