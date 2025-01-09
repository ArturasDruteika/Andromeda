cmake_minimum_required(VERSION 3.24)

project(SystemLauncher)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    main.cpp
)

# set working directory same as .exe to find resources from it
file(TO_CMAKE_PATH $<TARGET_FILE_DIR:${PROJECT_NAME}>// exe_dir)
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${exe_dir})

include_directories(
	..//EngineCore//EngineRunner//include//
)

target_link_libraries(${PROJECT_NAME} 
	PRIVATE 
		EngineCore
)

add_dependencies(${PROJECT_NAME} 
	EngineCore
)