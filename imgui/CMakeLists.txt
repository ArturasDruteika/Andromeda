cmake_minimum_required(VERSION 3.17.0)

project(imgui)
set(CMAKE_BUILD_PARALLEL_LEVEL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME}
	STATIC
		imgui/imconfig.h
		imgui/imgui.cpp
		imgui/imgui.h
		imgui/imgui_tables.cpp
		imgui/imgui_demo.cpp
		imgui/imgui_draw.cpp
		imgui/imgui_internal.h
		imgui/imgui_widgets.cpp
		imgui/imstb_rectpack.h
		imgui/imstb_textedit.h
		imgui/imstb_truetype.h
		imgui/backends/imgui_impl_opengl3.cpp
		imgui/backends/imgui_impl_opengl3.h
		imgui/backends/imgui_impl_glfw.cpp
		imgui/backends/imgui_impl_glfw.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

include_directories(
	imgui/
	imgui/backends
    ..//glfw//include//
    ..//glfw//src//
 )

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        glfw
)

add_dependencies(${PROJECT_NAME} 
    glfw
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}
    PREFIX 
        "ImGui"
    FILES
		imgui/imconfig.h
		imgui/imgui.cpp
		imgui/imgui.h
		imgui/imgui_tables.cpp
		imgui/imgui_demo.cpp
		imgui/imgui_draw.cpp
		imgui/imgui_internal.h
		imgui/imgui_widgets.cpp
		imgui/imstb_rectpack.h
		imgui/imstb_textedit.h
		imgui/imstb_truetype.h
		imgui/backends/imgui_impl_opengl3.cpp
		imgui/backends/imgui_impl_opengl3.h
		imgui/backends/imgui_impl_glfw.cpp
		imgui/backends/imgui_impl_glfw.h
)
