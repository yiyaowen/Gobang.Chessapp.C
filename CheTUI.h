#ifndef CHE_TUI_H
#define CHE_TUI_H


#ifndef TUI_GLOBALS
#define TUI_GLOBALS
////////////////////
// Globals of TUI //
////////////////////
#define PROMPT "#==> "
#define SELECT_ARROW "==>"

#endif /* TUI_GLOBALS */


#ifndef TUI_UTILS
#define TUI_UTILS
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

#define HIGHLIGHT_TEXT(originText)      "\033[01m" originText "\033[0m"
#define UNDERLINE_TEXT(originText)      "\033[04m" originText "\033[0m"
#define BLINK_TEXT(originText)          "\033[05m" originText "\033[0m"

#define RED_TEXT(originText)            "\033[31m" originText "\033[0m"
#define GREEN_TEXT(originText)          "\033[32m" originText "\033[0m"
#define YELLOW_TEXT(originText)         "\033[33m" originText "\033[0m"
#define BLUE_TEXT(originText)           "\033[34m" originText "\033[0m"
#define PURPLE_TEXT(originText)         "\033[35m" originText "\033[0m"
#define DARK_GREEN_TEXT(originText)     "\033[36m" originText "\033[0m"
#define WHITE_TEXT(originText)          "\033[37m" originText "\033[0m"

/* Default WIN */
#else
#define ClearScreen() do { \
    system("cls"); \
} while (0)

#endif

/* Universal Utils */
#define PrintSpaces(spacesNum) do { \
    printf("%" #spacesNum "s", ""); \
} while (0)

#endif /* TUI_UTILS */


#ifndef HOME_TUI
#define HOME_TUI
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

#define OPTION_PvP_NUM          1
#define OPTION_PvC_NUM          2
#define OPTION_PreAndSet_NUM    3
#define OPTION_AboutChe_NUM     4
#define OPTION_AboutPro_NUM     5
#define OPTION_Exit_NUM         6

#define HOME_OPTION_PvP             "<1> Player vs. Player\n"
#define HOME_OPTION_PvC             "<2> Player vs. `Chessplayer`\n"
#define HOME_OPTION_PreAndSet       "<3> Preferences & Settings\n"
#define HOME_OPTION_AboutChe        "<4> About `Chessplayer`\n"
#define HOME_OPTION_AboutPro        "<5> About `Gobang.Chessplayer.C`\n"
#define HOME_OPTION_Exit            "<6> Exit\n"

typedef const char * HOME_OPTIONS[HOME_OPTION_NUM];

void InitHomeOptionsArray();

void DisplayHomeOptions();

void DisplayHome();

void GetValidHomeOption();

int IsHomeOptionValid();

void SwitchToSelectedOption();

#endif /* HOME_TUI */


#ifndef BOARD_TUI
#define BORAD_TUI
///////////////
// Board TUI //
///////////////
#define BOARD_SIZE      15

/* iRount */
#define ROUND_BLACK         1
#define ROUND_WHITE         2

#define BLACK_TRI       10
#define WHITE_TRI       11
#define BLACK_CIR           20
#define WHITE_CIR           21

/* iErrorType */
#define POS_VALID           0
#define POS_OUT_OF_BOARD        1
#define POS_OVERLAPPED          2
#define POS_BAD_FORMAT          3

#define ClearInputBuffer(endChar) do { \
    while (getchar() != endChar) ; \
} while (0)

typedef int DEFAULT_FLAT_BOARD[BOARD_SIZE][BOARD_SIZE];

typedef struct {
    int x;
    char y;
} DEFAULT_FLAT_POSITION, POSITION;

void InitBoardArray();

void DisplayBoard();

void DisplayHint(int iRound);

void GetValidPosition(int iRound);

int IsPositionValid();

void DisplayErrorHint(int iErrorType);

int StartPvP();

#endif /* BORAD_TUI */


#endif /* CHE_TUI_H */
