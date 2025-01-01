cmake_minimum_required(VERSION 3.24)

project(SystemLauncher)
set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#SPDLOG
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/ spdlog_path)

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

### Post builds
# SPDLog
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD 
	COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different
    ${spdlog_root_path}//bin//$<$<CONFIG:debug>:spdlogd.dll>$<$<CONFIG:release>:spdlog.dll>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)