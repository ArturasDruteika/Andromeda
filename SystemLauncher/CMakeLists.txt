cmake_minimum_required(VERSION 3.24)

project(SystemLauncher)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    main.cpp
)

include_directories(
	..//Core//include//
)

target_link_libraries(${PROJECT_NAME} 
	PRIVATE 
		Core
)

add_dependencies(${PROJECT_NAME} 
	Core
)