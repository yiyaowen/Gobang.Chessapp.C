file(GLOB_RECURSE ChessappUtilitySourceFiles "*.c")
file(GLOB_RECURSE ChessappUtilityHeaderFiles "*.h")

add_library(utils STATIC
    ${ChessappUtilitySourceFiles}
    ${ChessappUtilityHeaderFiles}
)