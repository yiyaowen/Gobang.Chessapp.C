file(GLOB_RECURSE TextUserInterfaceSourceFiles
    "Page/*.c"
    "Route/*.c"
    TuiUserInteraction.c
)

file(GLOB_RECURSE TextUserInterfaceHeaderFiles
    "Page/*.h"
    "Route/*.h"
    TuiDefinitions.h
    TuiUserInteraction.h
    TuiUtility.h
)

if(CMAKE_HOST_WIN32)
    file(GLOB TuiWin32SourceFiles "win32/*.c")
    file(GLOB TuiWin32HeaderFiles "win32/*.h")
    list(APPEND TextUserInterfaceSourceFiles ${TuiWin32SourceFiles})
    list(APPEND TextUserInterfaceHeaderFiles ${TuiWin32HeaderFiles})
elseif(CMAKE_HOST_APPLE)
    file(GLOB TuiAppleSourceFiles "unix/*.c")
    file(GLOB TuiAppleHeaderFiles "unix/*.h")
    list(APPEND TextUserInterfaceSourceFiles ${TuiAppleSourceFiles})
    list(APPEND TextUserInterfaceHeaderFiles ${TuiAppleHeaderFiles})
elseif(CMAKE_HOST_UNIX)
    file(GLOB TuiUnixSourceFiles "unix/*.c")
    file(GLOB TuiUnixHeaderFiles "unix/*.h")
    list(APPEND TextUserInterfaceSourceFiles ${TuiUnixSourceFiles})
    list(APPEND TextUserInterfaceHeaderFiles ${TuiUnixHeaderFiles})
endif()

add_library(tui STATIC
    ${TextUserInterfaceSourceFiles}
    ${TextUserInterfaceHeaderFiles}
)