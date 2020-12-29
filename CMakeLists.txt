cmake_minimum_required(VERSION 3.10)

project(gobang-chessapp LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_HOST_WIN32)
    add_definitions("-D WIN")
    message("Current system: Windows")
elseif(CMAKE_HOST_APPLE)
    add_definitions("-D UNIX -D MACOS")
    message("Current system: macOS")
elseif(CMAKE_HOST_UNIX)
    add_definitions("-D UNIX")
    message("Current system: unix")
endif()

add_subdirectory(Src)
add_subdirectory(Gobang.Core.C)