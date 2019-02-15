cmake_minimum_required(VERSION 3.13)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)

add_executable(minesweeper
                main.cpp
                Field.cpp
                Field.h)