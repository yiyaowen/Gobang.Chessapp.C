#include <stdio.h> // fflush, printf, stdin
#include <stdlib.h> // system

/* Default WIN */
#ifndef WIN
#ifndef UNIX
#define WIN
#endif
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
#define ClearScreen() do { \
    system("cls"); \
} while (0)

/* UNIX */
#elif UNIX
#define ClearScreen() do { \
    system("clear"); \
} while (0)

#define BEGIN_ATTR(attr) do { \
    printf(attr); \
} while (0)

#define NONE_ATTR       "\033[00m"

#define HIGHLIGHT_ATTR          "\033[01m"
#define UNDERLINE_ATTR          "\033[04m" 
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
#define BLINK_TEXT(originText)          "\033[05m" originText "\033[25m"

#define BLACK_TEXT(originText)          "\033[30m" originText "\033[39m"
#define RED_TEXT(originText)            "\033[31m" originText "\033[39m"
#define GREEN_TEXT(originText)          "\033[32m" originText "\033[39m"
#define YELLOW_TEXT(originText)         "\033[33m" originText "\033[39m"
#define BLUE_TEXT(originText)           "\033[34m" originText "\033[39m"
#define PURPLE_TEXT(originText)         "\033[35m" originText "\033[39m"
#define DARK_GREEN_TEXT(originText)     "\033[36m" originText "\033[39m"
#define WHITE_TEXT(originText)          "\033[37m" originText "\033[39m"

#define BLACK_BACK(originText)          "\033[40m" originText "\033[49m"
#define RED_BACK(originText)            "\033[41m" originText "\033[49m"
#define GREEN_BACK(originText)          "\033[42m" originText "\033[49m"
#define YELLOW_BACK(originText)         "\033[43m" originText "\033[49m"
#define BLUE_BACK(originText)           "\033[44m" originText "\033[49m"
#define PURPLE_BACK(originText)         "\033[45m" originText "\033[49m"
#define DARK_GREEN_BACK(originText)     "\033[46m" originText "\033[49m"
#define WHITE_BACK(originText)          "\033[47m" originText "\033[49m"

#endif

/* Universal Utils */
#define PrintSpaces(spacesNum) do { \
    printf("%" #spacesNum "s", ""); \
} while (0)

#define ClearInputBuffer() do { \
    fflush(stdin); \
} while (0) 
// Don't use [getchar() != '\n';]
// That doesn't work well when [stdin] is empty

//////////////
// Home TUI //
//////////////

#define HOME_ICON \
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
  "\\\\<<<<<<<<<<<<<<<<<==<<<<<<<<<==<<<<<<<<<<<<<<<==<<<<<<<<<<<<<==<<<<<<<==<<<<<<<<<<//" "\n"

#define HOME_OPTION_NUM     6

#define OPTION_HOME_NUM     0
#define OPTION_PvP_NUM          1
#define OPTION_PvC_NUM          2
#define OPTION_PreAndSet_NUM    3
#define OPTION_AboutChe_NUM     4
#define OPTION_AboutPro_NUM     5
#define OPTION_Exit_NUM         6

#define HOME_OPTION_HOME    "<0> Home\m"
#define HOME_OPTION_PvP             "<1> Player vs. Player\n"
#define HOME_OPTION_PvC             "<2> Player vs. `Chessplayer`\n"
#define HOME_OPTION_PreAndSet       "<3> Preferences & Settings\n"
#define HOME_OPTION_AboutChe        "<4> About `Chessplayer`\n"
#define HOME_OPTION_AboutPro        "<5> About `Gobang.Chessplayer.C`\n"
#define HOME_OPTION_Exit            "<6> Exit\n"

typedef const char * HOME_OPTIONS[HOME_OPTION_NUM];

///////////////
// Board TUI //
///////////////

#define BOARD_SIZE      15

#define BLACK_TRI       10
#define WHITE_TRI       11
#define BLACK_CIR           20
#define WHITE_CIR           21

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
