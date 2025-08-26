cmake_minimum_required(VERSION 3.21)
project(s21matrix LANGUAGES CXX)

set(S21MATRIX_VERSION_MAJOR 1)
set(S21MATRIX_VERSION_MINOR 0)
set(S21MATRIX_VERSION_PATCH 0)
set(S21MATRIX_VERSION "${S21MATRIX_VERSION_MAJOR}.${S21MATRIX_VERSION_MINOR}.${S21MATRIX_VERSION_PATCH}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


option(S21MATRIX_TESTS "Build tests" ON)
option(S21MATRIX_BENCHMARKS "Build benchmarks" ON)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCES
    s21_matrix.cc
    s21_matrix_exception.cc
)

set(HEADERS
    s21_matrix.h
    s21_matrix_exception.h
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Configuring Release build")
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_LOWER)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

if(BUILD_TYPE_LOWER STREQUAL "debug")
    message(STATUS "Configuring DEBUG build")
    add_compile_options(
        -g
        -O0
        -DDEBUG
    )

    if(S21MATRIX_COVERAGE)
        message(STATUS "Enabling code coverage instrumentation")
        add_compile_options(--coverage)
        add_link_options(--coverage)
    endif()
else()
    message(STATUS "Configuring RELEASE build")
    add_compile_options(
        -O3
        -DNDEBUG
        -flto
    )
    add_link_options(-flto)
endif()

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES
    ${HEADERS}
    ${SOURCES}
)

add_library(s21matrix STATIC ${SOURCES} ${HEADERS})
set_target_properties(s21matrix PROPERTIES
    VERSION ${S21MATRIX_VERSION}
    SOVERSION ${S21MATRIX_VERSION_MAJOR}
    OUTPUT_NAME "s21matrix"
    POSITION_INDEPENDENT_CODE ON
    DEBUG_POSTFIX "_d"
)

target_include_directories(s21matrix PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS s21matrix
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES ${HEADERS} DESTINATION include/s21matrix)

if(S21MATRIX_TESTS)
    enable_testing()

    find_package(GTest REQUIRED)

    add_executable(s21matrix_tests
        tests/s21_matrix_tests.cpp
    )

    target_include_directories(s21matrix_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_link_libraries(s21matrix_tests
        PRIVATE
        s21matrix
        GTest::GTest
        GTest::Main
    )

    add_test(NAME s21matrix_tests COMMAND s21matrix_tests)
endif()

if(S21MATRIX_BENCHMARKS AND NOT BUILD_TYPE_LOWER STREQUAL "debug")
    if(APPLE)
        find_package(benchmark QUIET
            PATHS "/opt/homebrew/Cellar/google-benchmark/1.9.3/lib/cmake"
        )
    endif()
if(NOT benchmark_FOUND)
    message(WARNING "Google Benchmark not found - benchmarks will not be built")
    set(S21MATRIX_BENCHMARKS OFF)
else()
    message(STATUS "Found Google Benchmark: ${benchmark_VERSION}")

    add_executable(s21matrix_bench
        benchmarks/bench_matrix.cc
    )

    target_include_directories(s21matrix_bench PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_link_libraries(s21matrix_bench
        PRIVATE
        s21matrix
        benchmark::benchmark
    )
endif()
elseif(S21MATRIX_BENCHMARKS AND BUILD_TYPE_LOWER STREQUAL "debug")
    message(WARNING "Benchmarks are disabled in Debug build")
endif()
