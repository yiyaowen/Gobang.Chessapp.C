include_directories(
    "${CMAKE_SOURCE_DIR}/Gobang.Core.C/Interface" # Core Interface
    Chessapp.Main
    DataModel
    TextUserInterface
)

add_subdirectory(Chessapp.Main)
add_subdirectory(DataModel)
add_subdirectory(TextUserInterface)