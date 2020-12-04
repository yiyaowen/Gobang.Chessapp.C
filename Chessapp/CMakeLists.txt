cmake_minimum_required(VERSION 3.10)

project(gobang_chessplayer-chessapp LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(${CORE_PATH}/Interface)

file(GLOB_RECURSE c_src_files . *.c)

add_executable(Main
    ${c_src_files}
)

target_link_libraries(Main
    core
)
