cmake_minimum_required(VERSION 3.13)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)

add_executable(minesweeper
                main.cpp
                libs/Field.h
                libs/Enums.h
                libs/BaseField.cpp
                libs/BaseField.h
                libs/TermField.cpp
                libs/TermField.h
			  )
