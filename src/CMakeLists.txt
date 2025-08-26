cmake_minimum_required(VERSION 3.21)

project(Viewer3D
  VERSION 2.0.0
  LANGUAGES CXX
  DESCRIPTION "3D Viewer Application"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Werror -g)
endif()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)

add_subdirectory(third_party/s21matrix)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    # ${CMAKE_CURRENT_SOURCE_DIR}/s21matrix
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/core/math
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/s21matrix
)

set(SOURCES
  core/math/mat4x4.cpp
  core/math/vec2.cpp
  core/math/vec3.cpp
  core/math/vec4.cpp
)

set(HEADERS
  core/math/mat4x4.h
  core/math/vec2.h
  core/math/vec3.h
  core/math/vec4.h
)

add_executable(Viewer3D
  main.cpp
  ${SOURCES}
  ${HEADERS}
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES
  ${HEADERS}
  ${SOURCES}
  main.cpp
)

target_include_directories(Viewer3D PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/s21matrix>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(Viewer3D PRIVATE
    s21matrix
    # OpenGL::GL
    # GLEW::GLEW
    # glfw
)

include(GNUInstallDirs)
install(TARGETS Viewer3D
    EXPORT Viewer3DTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)


install(DIRECTORY core/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/core
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT Viewer3DTargets
    FILE Viewer3DTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Viewer3D
)

enable_testing()
add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
