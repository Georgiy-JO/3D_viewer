cmake_minimum_required(VERSION 3.21)
project(ViewerGTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O2 -DNDEBUG -Wall -Wextra)
else()
    add_compile_options(-g -O0 -Wall -Wextra -Werror)
endif()

option(BUILD_TESTS "Build tests" ON)
option(BUILD_COVERAGE "Enable code coverage" OFF)

if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)

    find_package(glm REQUIRED)

    set(INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}/../s21matrix
        ${CMAKE_CURRENT_SOURCE_DIR}/../core
        ${CMAKE_CURRENT_SOURCE_DIR}/../core/math
        ${gtest_SOURCE_DIR}/include
    )

    add_executable(mat4x4_glm_compatibility
        matrices_tests/mat4x4_glm_capability_tests.cpp
        ../core/math/mat4x4.cpp
        $<TARGET_OBJECTS:s21matrix>
    )

    target_include_directories(mat4x4_glm_compatibility PRIVATE ${INCLUDE_DIRS})
    target_compile_options(mat4x4_glm_compatibility PRIVATE -O2)
    target_link_libraries(mat4x4_glm_compatibility gtest_main glm::glm pthread)
    add_test(NAME Mat4GLMTest COMMAND mat4x4_glm_compatibility)

endif()
