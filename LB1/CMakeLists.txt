cmake_minimum_required(VERSION 3.17)
project(Laba1)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(
        -Wall
        -pedantic-errors
        -std=c++14
)

add_executable(Laba1 main.cpp MegaMatrix.h)