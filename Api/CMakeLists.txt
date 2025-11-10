cmake_minimum_required(VERSION 3.24)
project(Api LANGUAGES CXX)

add_library(Api STATIC)
set_target_properties(Api PROPERTIES LINKER_LANGUAGE CXX)  # <-- key line
target_compile_features(Api PUBLIC cxx_std_23)

set(API_INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(Api
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${API_INC}
        FILES
            ${API_INC}/IEngine.hpp
            ${API_INC}/IRenderer.hpp
            ${API_INC}/IScene.hpp
)

target_include_directories(Api
    PUBLIC
        $<BUILD_INTERFACE:${API_INC}>
        $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)
install(TARGETS Api EXPORT ApiTargets FILE_SET HEADERS)
install(EXPORT ApiTargets NAMESPACE Andromeda:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Api)
install(DIRECTORY ${API_INC}/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
