include_directories(
    "${CMAKE_SOURCE_DIR}/Gobang.Core.C/Interface" # Core Interface
    Chessapp.Main
    Chessapp.Utility
    DataModel
    TextUserInterface
)

if(CMAKE_HOST_WIN32)
    include_directories("TextUserInterface/win32")
elseif(CMAKE_HOST_APPLE)
    include_directories("TextUserInterface/unix")
elseif(CMAKE_HOST_UNIX)
    include_directories("TextUserInterface/unix")
endif()

add_subdirectory(Chessapp.Main)
add_subdirectory(Chessapp.Utility)
add_subdirectory(DataModel)
add_subdirectory(TextUserInterface)