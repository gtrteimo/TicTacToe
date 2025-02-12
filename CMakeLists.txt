cmake_minimum_required(VERSION 3.10)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
# add_executable(TicTacToe src/main.cpp src/glad.c src/TicTacToe.cpp src/TicTacToeUser.cpp src/TicTacToeGUI.cpp)
add_executable(TicTacToe src/main2.cpp src/glad.c)

target_compile_options(TicTacToe PRIVATE
    -std=c++20
    -fdiagnostics-color=always
    -pedantic-errors
    -Wall
    # -Weffc++
    -Wextra
    -Wconversion
    -Wsign-conversion
    -Werror
    -lGL
    -lGLU
    -lglut
    -lm
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Release>:-DNDEBUG>
)

find_package(glfw3 REQUIRED)

set_source_files_properties(src/glad.c PROPERTIES COMPILE_FLAGS "-w")

target_link_libraries(TicTacToe glfw GL)
