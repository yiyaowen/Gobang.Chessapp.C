cmake_minimum_required(VERSION 3.10)

project(gobang_chessplayer LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# get current platform
if (CMAKE_HOST_WIN32)
    add_definitions("-D WIN")
    message("Current platform: Windows")
elseif (CMAKE_HOST_APPLE)
    add_definitions("-D UNIX -D MACOS")
    message("Current platform: macOS")
elseif (CMAKE_HOST_UNIX)
    add_definitions("-D UNIX -D LINUX")
    message("Current platform: Linux")
endif ()

# global path
set(CHESSAPP_PATH ${CMAKE_SOURCE_DIR}/Chessapp)
set(CORE_PATH ${CMAKE_SOURCE_DIR}/Gobang.Core.C)

add_subdirectory(Chessapp)
add_subdirectory(Gobang.Core.C)
