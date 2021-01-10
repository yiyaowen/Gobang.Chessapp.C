#ifndef SMART_DISPLAY_H
#define SMART_DISPLAY_H

#include "ConsoleDoubleBuffer.h"

#define printClsErrorMessage() do { \
    printf("Error occurred while clearing console screen.\n"); \
    printf("Please find help in README.md to solve this problem.\n"); \
} while (0)

#define cls(hConsole) do { \
    COORD coordScreen = { 0, 0 }; \
    DWORD cCharsWritten; \
    CONSOLE_SCREEN_BUFFER_INFO csbi; \
    DWORD dwConSize; \
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) \
    { \
        printClsErrorMessage(); \
        exit(EXIT_FAILURE); \
    } \
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y; \
    if (!FillConsoleOutputCharacter(hConsole, \
        (TCHAR)' ', \
        dwConSize, \
        coordScreen, \
        &cCharsWritten)) \
    { \
        printClsErrorMessage(); \
        exit(EXIT_FAILURE); \
    } \
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) \
    { \
        printClsErrorMessage(); \
        exit(EXIT_FAILURE); \
    } \
    if (!FillConsoleOutputAttribute(hConsole, \
        csbi.wAttributes, \
        dwConSize, \
        coordScreen, \
        &cCharsWritten)) \
    { \
        printClsErrorMessage(); \
        exit(EXIT_FAILURE); \
    } \
    SetConsoleCursorPosition(hConsole, coordScreen); \
} while (0)

#define clearScreen() do { \
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); \
    cls(hStdOut); \
} while (0)

#define printWithDoubleBuffer(PRINT_PROCESS) do { \
    DWORD cChars = 0; \
    DWORD cAttrs = 0; \
    TCHAR* data = (TCHAR*)noNullMalloc(sizeof(TCHAR)*4000); \
    WORD* attr = (WORD*)noNullMalloc(sizeof(WORD)*4000); \
    PRINT_PROCESS; \
    fflush(stdout); \
    CONSOLE_SCREEN_BUFFER_INFO csbi; \
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); \
    GetConsoleScreenBufferInfo(hStdOut, &csbi); \
    ReadConsoleOutputCharacter(hStdOut, data, 4000, (COORD) { 0, 0 }, &cChars); \
    ReadConsoleOutputAttribute(hStdOut, attr, 4000, (COORD) { 0, 0 }, &cAttrs); \
    HANDLE hScreenBufferToActive = CONSOLE_DOUBLE_BUFFER_PHASE > 0 ? \
        hBackwardScreenBuffer : hForewardScreenBuffer; \
    WriteConsoleOutputCharacter(hScreenBufferToActive, data, 4000, (COORD) { 0, 0 }, &cChars); \
    WriteConsoleOutputAttribute(hScreenBufferToActive, attr, 4000, (COORD) { 0, 0 }, &cAttrs); \
    SetConsoleCursorPosition(hScreenBufferToActive, csbi.dwCursorPosition); \
    SetConsoleActiveScreenBuffer(hScreenBufferToActive); \
    CONSOLE_DOUBLE_BUFFER_PHASE = -CONSOLE_DOUBLE_BUFFER_PHASE; \
    free(data); data = NULL; \
    free(attr); attr = NULL; \
} while (0)

#define clearAndPrintWithDoubleBuffer(DISPLAY_PROCESS) do { \
    clearScreen(); \
    printWithDoubleBuffer(DISPLAY_PROCESS); \
} while (0)

#endif // SMART_DISPLAY_H