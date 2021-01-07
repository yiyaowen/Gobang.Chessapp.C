#ifndef CHESSAPP_DEFINITIONS_H
#define CHESSAPP_DEFINITIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "TuiDefinitions.h"

/* Default WIN */
#ifndef WIN
#ifndef UNIX
#define WIN
#endif
#endif

#ifdef WIN
#include <windows.h>
#ifndef UNICODE
#define UNICODE // Enable utf-8
#endif
#pragma warning(disable:4996) // Enable scanf of MSVC
#endif

#define abortWithMsg(msg) do { \
    printf(RED_TEXT(HIGHLIGHT_TEXT("%s\n")), msg); \
    exit(EXIT_FAILURE); \
} while (0)

#define BOARD_SIZE      15

typedef size_t Size;

typedef int Side;
#define SIDE_BLACK  -1
#define SIDE_EMPTY  0
#define SIDE_WHITE  1

#define isBlackSide(SIDE) ((SIDE) == SIDE_BLACK)
#define isWhiteSide(SIDE) ((SIDE) == SIDE_WHITE)
#define isEmptySide(SIDE) ((SIDE) == SIDE_EMPTY)

#define reverseSide(SIDE) ((SIDE) = -(SIDE))

#endif // CHESSAPP_DEFINITIONS_H
