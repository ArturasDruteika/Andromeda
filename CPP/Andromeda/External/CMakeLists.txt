cmake_minimum_required(VERSION 3.24)

project(AndromedaExternal)

add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(Glad)
add_subdirectory(imgui)
set(SPDLOG_BUILD_PIC ON CACHE BOOL "" FORCE)
add_subdirectory(spdlog)
