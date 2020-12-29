file(GLOB_RECURSE ChessappMainSourceFiles "*.c")
file(GLOB_RECURSE ChessappMainHeaderFiles "*.h")

add_executable(chessapp
    ${ChessappMainSourceFiles}
    ${ChessappMainHeaderFiles}
)

target_link_libraries(chessapp
    core
    datamodel
    tui
)