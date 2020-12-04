cmake_minimum_required(VERSION 3.10)

project(gobang_chessplayer-core LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(Src)
add_subdirectory(Test)
