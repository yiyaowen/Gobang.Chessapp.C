// ConsoleDoubleBuffer.h for win32
ifndef CONSOLE_DOUBLE_BUFFER_H
#define CONSOLE_DOUBLE_BUFFER_H

#include "ChessappDefinition.h"

extern HANDLE hForewardScreenBuffer;
extern HANDLE hBackwardScreenBuffer;
extern int CONSOLE_DOUBLE_BUFFER_PHASE;

#define enableConsoleDoubleBuffer() do { \
    hForewardScreenBuffer = CreateConsoleScreenBuffer( \
        GENERIC_READ | GENERIC_WRITE, \
        FILE_SHARE_READ | FILE_SHARE_WRITE, \
        NULL, \
        CONSOLE_TEXTMODE_BUFFER, \
        NULL \
    ); \
    hBackwardScreenBuffer = CreateConsoleScreenBuffer( \
        GENERIC_READ | GENERIC_WRITE, \
        FILE_SHARE_READ | FILE_SHARE_WRITE, \
        NULL, \
        CONSOLE_TEXTMODE_BUFFER, \
        NULL \
    ); \
    CONSOLE_DOUBLE_BUFFER_PHASE = 1; \
    SetConsoleActiveScreenBuffer(hForewardScreenBuffer); \
} while (0)

#endif // CONSOLE_DOUBLE_BUFFER_H