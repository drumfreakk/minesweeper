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
                libs/SFMLField.cpp
                libs/SFMLField.h
                libs/FieldTexture.cpp
                libs/FieldTexture.h
		libs/SFMLGame.cpp libs/SFMLGame.h)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.5 REQUIRED system graphics window network audio)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})