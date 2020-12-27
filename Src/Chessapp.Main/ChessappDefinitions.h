#ifndef INCLUDE_CHE_DEF_H
#define INCLUDE_CHE_DEF_H

#include <stdio.h> // printf, stdin
#include <stdlib.h> // system, exit
#include <stddef.h> // size_t
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
    printf(RED_TEXT(HIGHLIGHT_TEXT("%s")), msg); \
    putchar('\n'); \
    exit(EXIT_FAILURE); \
} while (0)

//////////////
// Game TUI //
//////////////

#define BOARD_SIZE      15

#define GRID_LEFT_TOP       1
#define GRID_RIGHT_TOP      2
#define GRID_RIGHT_BOTTOM   3
#define GRID_LEFT_BOTTOM    4
#define GRID_LEFT           5
#define GRID_TOP            6
#define GRID_RIGHT          7
#define GRID_BOTTOM         8
#define GRID_MIDDLE         9

#define BLACK_TRI       10
#define WHITE_TRI       11
#define BLACK_CIR           20
#define WHITE_CIR           21

/* WIN */

#define LEFT_TOP_ICON       "┏ "
#define TOP_ICON                "┯ "
#define RIGHT_TOP_ICON      "┓ "
#define LEFT_ICON               "┠ "
#define MIDDLE_ICON         "┼ "
#define RIGHT_ICON              "┨ "
#define LEFT_BOTTOM_ICON    "┗ "
#define BOTTOM_ICON             "┷ "
#define RIGHT_BOTTOM_ICON   "┛ "

#define GAME_INFO_FRAME_TOP         "//===>===>===>===>===>\\\\"
#define GAME_INFO_FRAME_MIDDLE      "||                    ||"
#define GAME_INFO_FRAME_BOTTOM    "\\\\<===<===<===<===<===//"

typedef int DEFAULT_FLAT_BOARD[BOARD_SIZE][BOARD_SIZE];

typedef struct {
    int x;
    char y;
    int status;
} DEFAULT_FLAT_POSITION, POSITION;

/* POSITION.status */
#define POS_QUIT    0
#define POS_PENDING     100
#define POS_VERIFIED    200

#define InitPos(pos) do { \
    pos.x = 1; \
    pos.y = 'A'; \
    pos.status = POS_PENDING; \
} while (0)

typedef struct {
    int i;
    int j;
} DEFAULT_ARRAY_POSITION, INDEXER;

typedef size_t Size;

///////////////
// Game data //
///////////////

typedef int Side;
#define SIDE_BLACK  -1
#define SIDE_EMPTY  0
#define SIDE_WHITE  1

#define isBlackSide(SIDE) ((SIDE) == SIDE_BLACK)
#define isWhiteSide(SIDE) ((SIDE) == SIDE_WHITE)

#define reverseSide(SIDE) ((SIDE) = -(SIDE))

#endif /* INCLUDE_CHE_DEF_H */
