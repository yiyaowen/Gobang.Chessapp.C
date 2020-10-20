#include <stdio.h> // fflush, printf, stdin
#include <stdlib.h> // system, exit

/* Default WIN */
#ifndef WIN
#ifndef UNIX
#define WIN
#endif
#endif

#ifdef WIN
#include <windows.h>
#pragma warning(disable:4996) // Enable scanf in VS
#endif

#ifndef _INCLUDE_CHE_DEF_H
#define _INCLUDE_CHE_DEF_H

////////////////////
// Globals of TUI //
////////////////////

#define PROMPT "○●○●>> "
#define SELECT_ARROW "○●○●>>"

//////////////////
// Utils of TUI //
//////////////////

/* WIN */
#ifdef WIN
#define EnableVirtualTerminalSequences() do { \
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); \
    if (hOut == INVALID_HANDLE_VALUE) { \
        printf("Can't enable Virtual Terminal Sequences on your Windows.\n"); \
        printf("Please make sure you are using the cmd of new type.\n"); \
        printf("Error - GetStdHandle(STD_OUTPUT_HANDLE);\n"); \
        exit(EXIT_FAILURE); \
    } \
    DWORD dwMode = 0; \
    if (!GetConsoleMode(hOut, &dwMode)) { \
        printf("Can't enable Virtual Terminal Sequences on your Windows.\n"); \
        printf("Please make sure you are using the cmd of new type.\n"); \
        printf("Error - GetConsoleMode(hOut, &dwMode);\n"); \
        exit(EXIT_FAILURE); \
    } \
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; \
    if (!SetConsoleMode(hOut, dwMode)) { \
        printf("Can't enable Virtual Terminal Sequences on your Windows.\n"); \
        printf("Please make sure you are using the cmd of new type.\n"); \
        printf("Error - SetConsoleMode(hOut, dwMode);\n"); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

#define ClearScreen() do { \
    system("cls"); \
} while (0)

/* UNIX */
#elif UNIX
#define EnableVirtualTerminalSequences() ;

#define ClearScreen() do { \
    system("clear"); \
} while (0)

#endif

/* Universal Utils */
#define BEGIN_ATTR(attr) do { \
    printf(attr); \
} while (0)

#define NONE_ATTR       "\033[00m"

#define HIGHLIGHT_ATTR          "\033[01m"
#define UNDERLINE_ATTR          "\033[04m"
// BLINK_ATTR of VT is deprecated on Windows
#define BLINK_ATTR              "\033[05m"

#define BLACK_F_ATTR            "\033[30m"
#define RED_F_ATTR              "\033[31m"
#define GREEN_F_ATTR            "\033[32m"
#define YELLOW_F_ATTR           "\033[33m"
#define BLUE_F_ATTR             "\033[34m"
#define PURPLE_F_ATTR           "\033[35m"
#define DARK_GREEN_F_ATTR       "\033[36m"
#define WHITE_F_ATTR            "\033[37m"

#define BLACK_B_ATTR            "\033[40m"
#define RED_B_ATTR              "\033[41m"
#define GREEN_B_ATTR            "\033[42m"
#define YELLOW_B_ATTR           "\033[43m"
#define BLUE_B_ATTR             "\033[44m"
#define PURPLE_B_ATTR           "\033[45m"
#define DARK_GREEN_B_ATTR       "\033[46m"
#define WHITE_B_ATTR            "\033[47m"

#define END_ATTR() do { \
    printf("\033[00m"); \
} while (0)

#define HIGHLIGHT_TEXT(originText)      "\033[01m" originText "\033[22m"
#define UNDERLINE_TEXT(originText)      "\033[04m" originText "\033[24m"
// BLINK_ATTR of VT is deprecated on Windows
#define BLINK_TEXT(originText)          "\033[05m" originText "\033[25m"

#define BLACK_TEXT(originText)          "\033[30m" originText "\033[39m"
#define RED_TEXT(originText)            "\033[31m" originText "\033[39m"
#define GREEN_TEXT(originText)          "\033[32m" originText "\033[39m"
#define YELLOW_TEXT(originText)         "\033[33m" originText "\033[39m"
#define BLUE_TEXT(originText)           "\033[34m" originText "\033[39m"
#define PURPLE_TEXT(originText)         "\033[35m" originText "\033[39m"
#define MAGENTA_TEXT(originText)        "\033[35m" originText "\033[39m"
#define DARK_GREEN_TEXT(originText)     "\033[36m" originText "\033[39m"
#define CYAN_TEXT(originText)           "\033[36m" originText "\033[39m"
#define WHITE_TEXT(originText)          "\033[37m" originText "\033[39m"

#define BLACK_BACK(originText)          "\033[40m" originText "\033[49m"
#define RED_BACK(originText)            "\033[41m" originText "\033[49m"
#define GREEN_BACK(originText)          "\033[42m" originText "\033[49m"
#define YELLOW_BACK(originText)         "\033[43m" originText "\033[49m"
#define BLUE_BACK(originText)           "\033[44m" originText "\033[49m"
#define PURPLE_BACK(originText)         "\033[45m" originText "\033[49m"
#define MAGENTA_BACK(originText)        "\033[45m" originText "\033[49m"
#define DARK_GREEN_BACK(originText)     "\033[46m" originText "\033[49m"
#define CYAN_BACK(originText)           "\033[46m" originText "\033[49m"
#define WHITE_BACK(originText)          "\033[47m" originText "\033[49m"

#define PrintSpaces(spacesNum) do { \
    printf("%" #spacesNum "s", ""); \
} while (0)

// Before using this you must make sure [stdin] is not empty
// Otherwise there will be a unthought stop
#define ClearInputBuffer() do { \
    char tmp; \
    while ((tmp = getchar()) != '\n' && tmp != EOF) ; \
} while (0) 

#define PutCharBack(c) do { \
    ungetc(c, stdin); \
} while (0)

//////////////
// Home TUI //
//////////////

#define HOME_ICON \
    "//========>>========>>========>>========>>========>>========>>========>>========>>\\\\" "\n" \
    "||  [Gobang News] Last Update: 2020-12-20 16:30                                   ||" "\n" \
    "||                                                                                ||" "\n" \
    "||                                                                                ||" "\n" \
    "||                                                                                ||" "\n" \
    "||                                                                                ||" "\n" \
    "||                                                                                ||" "\n" \
    "||                                                                                ||" "\n" \
    "||                                                                                ||" "\n" \
    "||                                                                                ||" "\n" \
    "||                                                                                ||" "\n" \
    "||                                                                                ||" "\n" \
    "||                                                                                ||" "\n" \
    "||                                                                                ||" "\n" \
  "\\\\<<========<<========<<========<<========<<========<<========<<========<<========//"

/* DEPRECATED */
/*
#define DEPRECATED_HOME_ICON \
    "//>>>>>>>>>>>>>>>>==>>>>>>>>>==>>>>>>>>>>>>>>>==>>>>>>>>>>>>>==>>>>>>>==>>>>>>>>>>>\\\\" "\n" \
    "||   ●●●●●●●●●●●                ●●●●●●●●●●●●●                                      ||" "\n" \
    "||  ●●●●●●●●●●●●●               ●●●●●●●●●●●●●●                                     ||" "\n" \
    "|| ●●●                          ●●●         ●●●                                    ||" "\n" \
    "|| ●●●                          ●●●         ●●●                                    ||" "\n" \
    "|| ●●●    ●●●●●●●●              ●●●●●●●●●●●●●●                                     ||" "\n" \
    "|| ●●●   ●●●●●●●●●●   ○○○○○○○   ●●●●●●●●●●●●●     ○○○○○○○○       ○○○○○○  ○○○○○○○○○ ||" "\n" \
    "|| ●●●    ●●●●●●●●●  ○○○○○○○○○  ●●●●●●●●●●●●●●   ○○○○○○○○○○     ○○○○○○○  ○○○   ○○○ ||" "\n" \
    "|| ●●●         ●●●●  ○○○   ○○○  ●●●         ●●●  ○○○   ○○○○     ○○   ○○  ○○○   ○○○ ||" "\n" \
    "|| ●●●         ●●●●  ○○○   ○○○  ●●●         ●●●  ○○○   ○○○○○    ○○   ○○  ○○○○○○○○○ ||" "\n" \
    "||  ●●●●●●●●●●●●●●   ○○○○○○○○○  ●●●●●●●●●●●●●●   ○○○○○○○○○○○○   ○○   ○○         ○○ ||" "\n" \
    "||   ●●●●●●●●●●●●     ○○○○○○○   ●●●●●●●●●●●●●     ○○○○○○○  ○○○  ○○   ○○         ○○ ||" "\n" \
    "||                                                                       ○○○○○○○○  ||" "\n" \
  "\\\\<<<<<<<<<<<<<<<<<==<<<<<<<<<==<<<<<<<<<<<<<<<==<<<<<<<<<<<<<==<<<<<<<==<<<<<<<<<<//"
*/

#define HOME_OPTION_NUM     6

#define OPTION_HOME_NUM     0
#define OPTION_PvP_NUM          1
#define OPTION_PvC_NUM          2
#define OPTION_PreAndSet_NUM    3
#define OPTION_AboutChe_NUM     4
#define OPTION_AboutPro_NUM     5
#define OPTION_Exit_NUM         6

#define HOME_OPTION_HOME    "<0> Home"
#define HOME_OPTION_PvP             "<1> Player vs. Player"
#define HOME_OPTION_PvC             "<2> Player vs. `Chessplayer`"
#define HOME_OPTION_PreAndSet       "<3> Preferences & Settings"
#define HOME_OPTION_AboutChe        "<4> About `Chessplayer`"
#define HOME_OPTION_AboutPro        "<5> About `Gobang.Chessplayer.C`"
#define HOME_OPTION_Exit            "<6> Exit"

typedef const char * HOME_OPTIONS[HOME_OPTION_NUM];

///////////////
// Board TUI //
///////////////

#define BOARD_SIZE      15

#define BLACK_TRI       10
#define WHITE_TRI       11
#define BLACK_CIR           20
#define WHITE_CIR           21

#ifdef WIN
#define BLACK_TRI_ICON  "▲"
#define BLACK_CIR_ICON      "●"
#define WHITE_TRI_ICON  "△"
#define WHITE_CIR_ICON      "○"
#elif UNIX
#define BLACK_TRI_ICON  "▲ "
#define BLACK_CIR_ICON      "● "
#define WHITE_TRI_ICON  "△ "
#define WHITE_CIR_ICON      "○ "
#endif

#define LEFT_TOP_ICON       "┏ "
#define TOP_ICON                "┯ "
#define RIGHT_TOP_ICON      "┓"
#define LEFT_ICON               "┠ "
#define MIDDLE_ICON         "┼ "
#define RIGHT_ICON              "┨"
#define LEFT_BOTTOM_ICON    "┗ "
#define BOTTOM_ICON             "┷ "
#define RIGHT_BOTTOM_ICON   "┛"

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

#endif /* _INCLUDE_CHE_DEF_H */
