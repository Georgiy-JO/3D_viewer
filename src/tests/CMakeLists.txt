cmake_minimum_required(VERSION 3.21)
project(ViewerGTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O2 -DNDEBUG -Wall -Wextra)
else()
    add_compile_options(
        -g 
        -O0 
        -Wall 
        -Werror 
        -Wextra 
        -D_POSIX_C_SOURCE=201706L)
endif()

option(BUILD_TESTS "Build tests" ON)
option(BUILD_COVERAGE "Enable code coverage" ON)

if(BUILD_TESTS OR BUILD_COVERAGE)
    find_program(VALGRIND_EXECUTABLE valgrind)
    find_program(LCOV_EXECUTABLE lcov)
    find_program(GENHTML_EXECUTABLE genhtml)
    find_package(glm REQUIRED)

    set(INBOUND_MODEL_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}/../core/math
        ${CMAKE_CURRENT_SOURCE_DIR}/../model
        ${CMAKE_CURRENT_SOURCE_DIR}/../model/model3d
        ${CMAKE_CURRENT_SOURCE_DIR}/../model/model3d/elements
        ${CMAKE_CURRENT_SOURCE_DIR}/../model/parser
        ${CMAKE_CURRENT_SOURCE_DIR}/../model/parser/service_functions
    )

    set(INBOUND_MODEL_SRC
        ../model/model3d/model3d.cpp
        ../model/model3d/elements/axisbounds.cpp
        ../model/model3d/elements/edges.cpp
        ../model/model3d/elements/vertices.cpp
        ../core/math/vec3.cpp

        ../model/parser/parser_src/parser.cpp
        ../model/parser/parser_src/model_parser.cpp
        ../model/parser/parser_src/model_alterers.cpp
        ../model/parser/parser_src/prefix_handlers.cpp
        ../model/parser/service_functions/service_functions.cpp
    )

    set(INBOUND_MODEL_TEST_SRC
        model/model3d.cpp
        model/parser.cpp
    )

    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)


    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../../materials/models
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

endif()

if(BUILD_TESTS)
    # mat4x4 tests
    set(INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        # ${CMAKE_CURRENT_SOURCE_DIR}/../s21matrix
        ${CMAKE_CURRENT_SOURCE_DIR}/../core
        ${CMAKE_CURRENT_SOURCE_DIR}/../core/math
        ${gtest_SOURCE_DIR}/include
    )

    add_executable(mat4x4_glm_compatibility
        mat4x4/mat4x4_glm_capability_tests.cpp
        ../core/math/mat4x4.cpp
        ../core/math/vec2.cpp
        ../core/math/vec3.cpp
        ../core/math/vec4.cpp
        $<TARGET_OBJECTS:s21matrix>
    )

    target_include_directories(mat4x4_glm_compatibility PRIVATE ${INCLUDE_DIRS})
    target_compile_options(mat4x4_glm_compatibility PRIVATE -O2)
    target_link_libraries(mat4x4_glm_compatibility gtest_main glm::glm pthread)
    add_test(NAME Mat4GLMTest COMMAND mat4x4_glm_compatibility)


    # Inbound model tests
    add_executable(inbound_model_tests
        ${INBOUND_MODEL_TEST_SRC}       # <- test code files
        ${INBOUND_MODEL_SRC}
    )

    target_include_directories(inbound_model_tests PRIVATE ${INBOUND_MODEL_INCLUDE_DIRS})
    target_link_libraries(inbound_model_tests PRIVATE gtest_main pthread)
    set_property(TARGET inbound_model_tests PROPERTY CXX_STANDARD 20)
    add_test(NAME ModelTests COMMAND inbound_model_tests)

    add_custom_target(run_inbound_model_tests
        COMMAND inbound_model_tests
        DEPENDS inbound_model_tests
        COMMENT "Running inbound_model_tests executable"
    )

    if(VALGRIND_EXECUTABLE)
        add_custom_target(valgrind_inbound_model_tests
            COMMAND valgrind 
                --tool=memcheck  
                --leak-check=full 
                --show-leak-kinds=all 
                --track-origins=yes 
                --verbose 
                --log-file=valgrind_inbound_model_tests.txt
                $<TARGET_FILE:inbound_model_tests>
            DEPENDS inbound_model_tests
            COMMENT "Running inbound_model_tests under Valgrind (see valgrind_inbound_model_tests.txt)"
        )
    else()
        message(WARNING "Valgrind not found. valgrind_inbound_model_tests target will not be available.")
    endif()
endif()

if(BUILD_COVERAGE AND LCOV_EXECUTABLE AND GENHTML_EXECUTABLE)

    add_executable(inbound_model_cov
        ${INBOUND_MODEL_TEST_SRC}       # <- test code files
        ${INBOUND_MODEL_SRC}
    )

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY CMAKE_COVERAGE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    
    target_compile_options(inbound_model_cov  PRIVATE
        -fprofile-arcs 
        -ftest-coverage
    )
    target_include_directories(inbound_model_cov PRIVATE ${INBOUND_MODEL_INCLUDE_DIRS})
    target_link_libraries(inbound_model_cov PRIVATE gtest_main pthread --coverage)


    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E remove_directory coverage
        COMMAND ${CMAKE_COMMAND} -E make_directory coverage

        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/inbound_model_cov

        COMMAND ${LCOV_EXECUTABLE} --capture --directory ${CMAKE_CURRENT_BINARY_DIR}  --output-file coverage/coverage_1.info --ignore-errors mismatch --path ${CMAKE_CURRENT_BINARY_DIR}/..
        COMMAND ${LCOV_EXECUTABLE} --remove coverage/coverage_1.info '/usr/*' 'gtest/*' 'tests/*' --output-file coverage/coverage.info
        COMMAND ${CMAKE_COMMAND} -E remove -f coverage/coverage_1.info
        COMMAND ${GENHTML_EXECUTABLE} --output-directory=coverage coverage/coverage.info

        # COMMAND find ${CMAKE_CURRENT_BINARY_DIR} -name "*.gcda" -o -name "*.gcno" -delete         # isues may cause these
        # COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_CURRENT_BINARY_DIR}/inbound_model_cov

        DEPENDS inbound_model_cov
        COMMENT "Running tests + Generating HTML coverage report in ./coverage"
    )

else()
    message(WARNING "Coverage tools not found or BUILD_COVERAGE is OFF. coverage target will not be available.")
endif()
