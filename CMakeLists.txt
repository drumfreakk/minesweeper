
cmake_minimum_required(VERSION 3.13)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)

add_executable(minesweeper
				src/main.cpp
				include/field.h
				include/enums.h
				src/basefield.cpp
				include/basefield.h
				src/termfield.cpp
				include/termfield.h
				)
