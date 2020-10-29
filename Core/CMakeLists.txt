cmake_minimum_required(VERSION 3.10)

project(chess-core LANGUAGES C)
add_definitions(-std=c11)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(Src)
add_subdirectory(Test)
