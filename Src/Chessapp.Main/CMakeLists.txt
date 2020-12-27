file(GLOB_RECURSE ChessappMainSourceFiles . "*.c")

add_executable(chessapp ${ChessappMainSourceFiles})

target_link_libraries(chessapp
    core
    datamodel
    tui
)