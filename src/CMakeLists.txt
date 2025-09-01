cmake_minimum_required(VERSION 3.21)

project(Viewer3D
  VERSION 2.0.0
  LANGUAGES CXX
  DESCRIPTION "3D Viewer Application"
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Werror -g)
endif()


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)          #new
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets Widgets)     #new
find_package(OpenGL REQUIRED)

# find_package(GLEW REQUIRED)   # for GLFW3 and GLEW
# find_package(GLFW3 REQUIRED)  # for GLFW3 and GLEW

#find_package(Qt6 COMPONENTS Core Gui Widgets OpenGLWidgets REQUIRED) # for qt6

# set(QT_GL_LIBS                                                      # for qt6
#   Qt6::Core
#   Qt6::Gui
#   Qt6::OpenGL                                                       # ??
#   Qt6::Widgets                                                      # ??
#   Qt6::OpenGLWidgets
#   OpenGL::GL
# )

# set_target_properties(${PROJECT_NAME} PROPERTIES                    # for qt6
#   AUTOMOC ON
#   AUTOUIC ON
#   AUTORCC ON
# )

set(INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/core
  ${CMAKE_CURRENT_SOURCE_DIR}/core/math
  ${CMAKE_CURRENT_SOURCE_DIR}/controller
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/s21_matrix
  ${CMAKE_CURRENT_SOURCE_DIR}/model
  ${CMAKE_CURRENT_SOURCE_DIR}/model/model3d
  ${CMAKE_CURRENT_SOURCE_DIR}/model/model3d/elements
  ${CMAKE_CURRENT_SOURCE_DIR}/model/parser
  ${CMAKE_CURRENT_SOURCE_DIR}/model/parser/service_functions
  ${CMAKE_CURRENT_SOURCE_DIR}/model/render
  ${CMAKE_CURRENT_SOURCE_DIR}/model/render/uniforms
  ${CMAKE_CURRENT_SOURCE_DIR}/view
  ${CMAKE_CURRENT_SOURCE_DIR}/view/model_controles
  ${CMAKE_CURRENT_SOURCE_DIR}/view/model_controles/slider
  ${CMAKE_CURRENT_SOURCE_DIR}/view/model_viewer
  ${CMAKE_CURRENT_SOURCE_DIR}/view/ui
)

set(SOURCES
  core/math/matrix4x4.cpp
  core/math/vec2.cpp
  core/math/vec3.cpp
  core/math/vec4.cpp
  model/model3d/model3d.cpp
  model/model3d/elements/vertices.cpp
  model/model3d/elements/edges.cpp
  model/model3d/elements/axisbounds.cpp
  model/parser/parser_src/parser.cpp
  model/parser/parser_src/model_alterers.cpp
  model/parser/parser_src/prefix_handlers.cpp
  model/parser/parser_src/model_parser.cpp
  model/parser/service_functions/service_functions.cpp
  model/render/render_src/gui_model.cpp
  model/render/render_src/shader_program.cpp
  model/render/uniforms/uniforms.cpp
  view/ui/mainwindow.cpp
  view/ui/mainwindow.ui
  view/model_viewer/model_viewer_src/model_viewer.cpp
  view/model_viewer/model_viewer_src/mouse_actions.cpp
  view/model_controles/elements/slider.cpp
  controller/model_parser_worker.cpp
  main.cpp
  third_party/s21_matrix/matrix.cpp
)

set(HEADERS
  core/math/matrix4x4.h
  core/math/vec2.h
  core/math/vec3.h
  core/math/vec4.h
  model/model3d/model3d.h
  model/model3d/elements/mesh.h
  model/model3d/elements/axisbounds.h
  model/parser/parser.h
  model/parser/model_parser.h
  model/parser/service_functions/service_functions.h
  view/ui/mainwindow.h
  view/model_viewer/model_viewer.h
  view/model_viewer/mouse_actions.h
  view/model_controles/model_controles.h
  view/model_controles/elements/slider.h
  controller/model_parser_worker.h
  controller/render_controller.h
  third_party/s21_matrix/matrix_exceptions.hpp
  third_party/s21_matrix/matrix_service.hpp
  third_party/s21_matrix/matrix.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    add_executable(Viewer3D
        ${SOURCES}
        ${HEADERS}
    )
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/model/render/shaders
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../materials/models
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
endif()

add_custom_target(run_Viewer3D
    COMMAND Viewer3D
    DEPENDS Viewer3D
    COMMENT "Running Viewer3D executable"
)

find_program(CLANG_FORMAT_EXE
    NAMES clang-format clang-format-20 clang-format-14 clang-format-13
    DOC "Path to clang-format executable"
)

if(CLANG_FORMAT_EXE)
    set(ALL_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/**/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/**/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/model/**/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/model/**/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/model/**/**/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/model/**/**/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/view/**/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/view/**/*.h
        # ${CMAKE_CURRENT_SOURCE_DIR}/controller/**/*.cpp
        # ${CMAKE_CURRENT_SOURCE_DIR}/controller/**/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/**/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/**/*.h
    )

    file(GLOB_RECURSE FORMAT_SOURCE_FILES
        LIST_DIRECTORIES false
        ${ALL_SOURCE_FILES}
    )

    list(FILTER FORMAT_SOURCE_FILES EXCLUDE REGEX ".*/third_party/.*")
    list(FILTER FORMAT_SOURCE_FILES EXCLUDE REGEX ".*/build/.*")

    if(FORMAT_SOURCE_FILES)
        add_custom_target(fix-style
            COMMAND ${CLANG_FORMAT_EXE}
                --style=file
                -i
                ${FORMAT_SOURCE_FILES}
            COMMENT "Applying Google code style..."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VERBATIM
        )

        add_custom_target(check-style
            COMMAND ${CLANG_FORMAT_EXE}
                --style=file:${CLANG_FORMAT_CONFIG}
                --dry-run
                --Werror
                ${FORMAT_SOURCE_FILES}
            COMMENT "Checking Google code style compliance..."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VERBATIM
        )

        message(STATUS "clang-format found: ${CLANG_FORMAT_EXE}")
        message(STATUS "Code style targets: check-style, fix-style")
        message(STATUS "Files to check: ${FORMAT_SOURCE_FILES} files")
    else()
        message(WARNING "No source files found for code style checking!")
    endif()
else()
    message(WARNING "clang-format not found! Code style targets unavailable.")
endif()

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES
  ${HEADERS}
  ${SOURCES}
)

target_include_directories(Viewer3D PUBLIC
    $<BUILD_INTERFACE:${INCLUDE_DIRS}>     #new
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/s21_matrix>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(Viewer3D PRIVATE
    # s21_matrix
    Qt${QT_VERSION_MAJOR}::Widgets     #new
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets      #new
    OpenGL::GLU       #new
    OpenGL::GL      #new
    # ${MY_QT_LIBS}  # for qt6
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
