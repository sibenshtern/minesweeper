cmake_minimum_required(VERSION 3.23)
project(minesweeper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FLTK_SKIP_FLUID True)
set(OpenGL_GL_PREFERENCE "GLVND")

find_package(FLTK REQUIRED)
find_package(OpenGL REQUIRED)

set(GRAPHLIB_DIR ".")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(
        ${GRAPHLIB_DIR}
        SYSTEM
        ${FLTK_INCLUDE_DIR}/../lib
)

add_executable(minesweeper main.cpp board.cpp cell.cpp minesweeper.cpp
        ${GRAPHLIB_DIR}/Graph_lib/Graph.cpp
        ${GRAPHLIB_DIR}/Graph_lib/Graph.h
        ${GRAPHLIB_DIR}/Graph_lib/GUI.cpp
        ${GRAPHLIB_DIR}/Graph_lib/GUI.h
        ${GRAPHLIB_DIR}/Graph_lib/Window.cpp
        ${GRAPHLIB_DIR}/Graph_lib/Window.h
        )

target_link_libraries(
        minesweeper
        ${FLTK_LIBRARIES}
        ${OPENGL_LIBRARIES}
        jpeg
        png
        Xinerama
        Xfixes
        Xcursor
        Xft
        Xrender
        fontconfig
)

install(TARGETS minesweeper)