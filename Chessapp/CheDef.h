#ifndef INCLUDE_CHE_DEF_H
#define INCLUDE_CHE_DEF_H

#include <stdio.h> // printf, stdin
#include <stdlib.h> // system, exit

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

#ifndef CHE_DOUBLE_BUFFER_VARIABLE
#define CHE_DOUBLE_BUFFER_VARIABLE
HANDLE hForeward;
HANDLE hBackward;
int CHE_DOUBLE_BUFFER_STATE;
#endif

// Include double buffer
#define INCLUDE_DOUBLE_BUFFER \
extern HANDLE hForeward; \
extern HANDLE hBackward; \
extern int CHE_DOUBLE_BUFFER_STATE;

#elif UNIX
#define INCLUDE_DOUBLE_BUFFER ;

#endif

////////////////////
// Globals of TUI //
////////////////////

#define PROMPT "○●○●>> "
#define SELECT_ARROW "○●○●>>"

//////////////////
// Utils of TUI //
//////////////////

/////////
/* WIN */
/////////
#ifdef WIN
#define EnableConsoleDoubleBuffer() do { \
    hForeward = CreateConsoleScreenBuffer( \
        GENERIC_READ | GENERIC_WRITE, \
        FILE_SHARE_READ | FILE_SHARE_WRITE, \
        NULL, \
        CONSOLE_TEXTMODE_BUFFER, \
        NULL \
    ); \
    hBackward = CreateConsoleScreenBuffer( \
        GENERIC_READ | GENERIC_WRITE, \
        FILE_SHARE_READ | FILE_SHARE_WRITE, \
        NULL, \
        CONSOLE_TEXTMODE_BUFFER, \
        NULL \
    ); \
    CHE_DOUBLE_BUFFER_STATE = 1; \
    SetConsoleActiveScreenBuffer(hForeward); \
} while (0)

#define printVTSErrorMessage() do { \
    printf("Can't enable Virtual Terminal Sequences on your Windows.\n"); \
    printf("Please make sure you are using the new cmd.exe.\n"); \
} while (0)

#define EnableVirtualTerminalSequences() do { \
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); \
    if (hOut == INVALID_HANDLE_VALUE) { \
        printVTSErrorMessage(); \
        printf("Error - GetStdHandle(STD_OUTPUT_HANDLE);\n"); \
        exit(EXIT_FAILURE); \
    } \
    DWORD dwMode = 0; \
    if (!GetConsoleMode(hOut, &dwMode)) { \
        printVTSErrorMessage(); \
        printf("Error - GetConsoleMode(hOut, &dwMode);\n"); \
        exit(EXIT_FAILURE); \
    } \
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; \
    if (!SetConsoleMode(hOut, dwMode)) { \
        printVTSErrorMessage(); \
        printf("Error - SetConsoleMode(hOut, dwMode);\n"); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

#define printClsErrorMessage() do { \
    printf("Error occurred while clearing console screen.\n"); \
    printf("Please find help in the BUILD-HELP flie to solve this problem.\n"); \
} while (0)

#define cls(hConsole) do { \
    COORD coordScreen = { 0, 0 }; /* Original caret position */ \
    DWORD cCharsWritten; \
    CONSOLE_SCREEN_BUFFER_INFO csbi; \
    DWORD dwConSize; \
    /* Get number of characters of current buffer */ \
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) \
    { \
        printClsErrorMessage(); \
        exit(EXIT_FAILURE); \
    } \
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y; \
    /* Fill screen with white-spaces */ \
    if (!FillConsoleOutputCharacter(hConsole, \
        (TCHAR)' ', \
        dwConSize, \
        coordScreen, \
        &cCharsWritten)) \
    { \
        printClsErrorMessage(); \
        exit(EXIT_FAILURE); \
    } \
    /* Get current buffer's attributes */ \
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) \
    { \
        printClsErrorMessage(); \
        exit(EXIT_FAILURE); \
    } \
    /* Reset current buffer's attributes */ \
    if (!FillConsoleOutputAttribute(hConsole, \
        csbi.wAttributes, \
        dwConSize, \
        coordScreen, \
        &cCharsWritten)) \
    { \
        printClsErrorMessage(); \
        exit(EXIT_FAILURE); \
    } \
    /* Put caret to original position */ \
    SetConsoleCursorPosition(hConsole, coordScreen); \
} while (0)

#define ClearScreen() do { \
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); \
    cls(hStdOut); \
} while (0)

#define autoprint(PRINT_PROCESS) do { \
    DWORD cChars = 0; \
    DWORD cAttrs = 0; \
    TCHAR data[4000]; \
    WORD attr[4000]; \
    PRINT_PROCESS; \
    CONSOLE_SCREEN_BUFFER_INFO csbi; \
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); \
    GetConsoleScreenBufferInfo(hStdOut, &csbi); \
    /* Copy chars and attrs from [stdout] to [double_buffer] */ \
    ReadConsoleOutputCharacter(hStdOut, data, 4000, (COORD) { 0, 0 }, &cChars); \
    ReadConsoleOutputAttribute(hStdOut, attr, 4000, (COORD) { 0, 0 }, &cAttrs); \
    WriteConsoleOutputCharacter(CHE_DOUBLE_BUFFER_STATE > 0 ? hBackward : hForeward, data, 4000, (COORD) { 0, 0 }, &cChars); \
    WriteConsoleOutputAttribute(CHE_DOUBLE_BUFFER_STATE > 0 ? hBackward : hForeward, attr, 4000, (COORD) { 0, 0 }, &cAttrs); \
    SetConsoleCursorPosition(CHE_DOUBLE_BUFFER_STATE > 0 ? hBackward : hForeward, csbi.dwCursorPosition); \
    /* Change display buffer */ \
    SetConsoleActiveScreenBuffer(CHE_DOUBLE_BUFFER_STATE > 0 ? hBackward : hForeward); \
    CHE_DOUBLE_BUFFER_STATE = -CHE_DOUBLE_BUFFER_STATE; \
} while (0)

#define autodisplay(DISPLAY_PROCESS) do { \
    ClearScreen(); \
    autoprint(DISPLAY_PROCESS); \
} while (0)

//////////
/* UNIX */
//////////
#elif UNIX
#define EnableConsoleDoubleBuffer() ;

#define EnableVirtualTerminalSequences() ;

#define ClearScreen() do { \
    system("clear"); \
} while (0)

#define autoprint(PRINT_PROCESS) do { \
    PRINT_PROCESS; \
} while (0)

#define autodisplay(DISPLAY_PROCESS) do { \
    ClearScreen(); \
    DISPLAY_PROCESS; \
} while (0)

#endif

///////////////
/* Universal */
///////////////
#define BEGIN_ATTR(attr) do { \
    printf(attr); \
} while (0)

#define NONE_ATTR       "\033[00m"

#ifdef WIN
// VTS's default attributes don't work well on Windows.
// Use white-foreground with black-background instead.
#define DEFAULT_F_ATTR  "\033[37m"
#define DEFAULT_B_ATTR  "\033[40m"
#elif UNIX
#define DEFAULT_F_ATTR  "\033[39m"
#define DEFAULT_B_ATTR  "\033[49m"
#endif
#define DEFAULT_ATTR    DEFAULT_F_ATTR DEFAULT_B_ATTR

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
    printf(DEFAULT_ATTR); \
} while (0)

#define HIGHLIGHT_TEXT(originText)      "\033[01m" originText "\033[22m"
#define UNDERLINE_TEXT(originText)      "\033[04m" originText "\033[24m"
// BLINK_TEXT of VT is deprecated on Windows
#define BLINK_TEXT(originText)          "\033[05m" originText "\033[25m"

#define BLACK_TEXT(originText)          "\033[30m" originText DEFAULT_F_ATTR
#define RED_TEXT(originText)            "\033[31m" originText DEFAULT_F_ATTR
#define GREEN_TEXT(originText)          "\033[32m" originText DEFAULT_F_ATTR
#define YELLOW_TEXT(originText)         "\033[33m" originText DEFAULT_F_ATTR
#define BLUE_TEXT(originText)           "\033[34m" originText DEFAULT_F_ATTR
#define PURPLE_TEXT(originText)         "\033[35m" originText DEFAULT_F_ATTR
#define MAGENTA_TEXT(originText)        "\033[35m" originText DEFAULT_F_ATTR
#define DARK_GREEN_TEXT(originText)     "\033[36m" originText DEFAULT_F_ATTR
#define CYAN_TEXT(originText)           "\033[36m" originText DEFAULT_F_ATTR
#define WHITE_TEXT(originText)          "\033[37m" originText DEFAULT_F_ATTR

#define BLACK_BACK(originText)          "\033[40m" originText DEFAULT_B_ATTR
#define RED_BACK(originText)            "\033[41m" originText DEFAULT_B_ATTR
#define GREEN_BACK(originText)          "\033[42m" originText DEFAULT_B_ATTR
#define YELLOW_BACK(originText)         "\033[43m" originText DEFAULT_B_ATTR
#define BLUE_BACK(originText)           "\033[44m" originText DEFAULT_B_ATTR
#define PURPLE_BACK(originText)         "\033[45m" originText DEFAULT_B_ATTR
#define MAGENTA_BACK(originText)        "\033[45m" originText DEFAULT_B_ATTR
#define DARK_GREEN_BACK(originText)     "\033[46m" originText DEFAULT_B_ATTR
#define CYAN_BACK(originText)           "\033[46m" originText DEFAULT_B_ATTR
#define WHITE_BACK(originText)          "\033[47m" originText DEFAULT_B_ATTR

#define PrintSpaces(spacesNum) do { \
    printf("%" #spacesNum "s", ""); \
} while (0)

// Before using this you must make sure [stdin] is not empty,
// otherwise there will be a unthought stop. One solution is that
// after getting '\n' use PutCharBack() to put it back.
#define ClearInputBuffer() do { \
    char tmp; \
    while ((tmp = getchar()) != '\n' && tmp != EOF) ; \
} while (0) 

#define PutCharBack(c) do { \
    ungetc(c, stdin); \
} while (0)

#define AbortWithMsg(msg) do { \
    printf(RED_TEXT(HIGHLIGHT_TEXT("%s")), msg); \
    putchar('\n'); \
} while (0)

////////////////
// Global TUI //
////////////////

/* Route status */
#define ROUTE_OVER      1
#define ROUTE_CONTINUE  2

/* Route exit_status */
#define ROUTE_SUCCESS EXIT_SUCCESS
#define ROUTE_FAILURE EXIT_FAILURE

/* Page IDs  */
#define PAGE_ID_Home            0
#define PAGE_ID_PvP             1
#define PAGE_ID_PvC             2
#define PAGE_ID_PreAndSet       3
#define PAGE_ID_MusicSound      31
#define PAGE_ID_NetworkConfig   32
#define PAGE_ID_AboutChe        4
#define PAGE_ID_AboutPro        5

/* Page names */
#define PAGE_NAME_Home            "Home"
#define PAGE_NAME_PvP             "PvP"
#define PAGE_NAME_PvC             "PvC"
#define PAGE_NAME_PreAndSet       "PreAndSet"
#define PAGE_NAME_MusicSound      "MusicSound"
#define PAGE_NAME_NetworkConfig   "NetworkConfig"
#define PAGE_NAME_AboutChe        "AboutChe"
#define PAGE_NAME_AboutPro        "AboutPro"

/* Page descriptions */
#define PAGE_DESC_Home          "Home"
#define PAGE_DESC_PvP           "Player versus Player"
#define PAGE_DESC_PvC           "Player versus Chessplayer"
#define PAGE_DESC_PreAndSet     "Preferences and Settings"
#define PAGE_DESC_MusicSound    "Music and Sound"
#define PAGE_DESC_NetworkConfig "Network Configuration"
#define PAGE_DESC_AboutChe      "About Chessplayer"
#define PAGE_DESC_AboutPro      "About `Gobang.Chessplayer.C` Project"

///////////////
// TUI Utils //
///////////////

#define OPTION_Confirm_NUM -2002

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

#define HOME_OPTION_NUM     6

#define OPTION_Home_NUM     0
#define OPTION_PvP_NUM          1
#define OPTION_PvC_NUM          2
#define OPTION_PreAndSet_NUM    3
#define OPTION_AboutChe_NUM     4
#define OPTION_AboutPro_NUM     5
#define OPTION_Exit_NUM         6

#define HOME_OPTION_PvP             "<1> Player vs. Player"
#define HOME_OPTION_PvC             "<2> Player vs. `Chessplayer`"
#define HOME_OPTION_PreAndSet       "<3> Preferences & Settings"
#define HOME_OPTION_AboutChe        "<4> About `Chessplayer`"
#define HOME_OPTION_AboutPro        "<5> About `Gobang.Chessplayer.C`"
#define HOME_OPTION_Exit            "<6> Exit"

typedef const char * HOME_OPTIONS[HOME_OPTION_NUM];

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
#ifdef WIN
#define BLACK_TRI_ICON  "▲"
#define BLACK_CIR_ICON      "●"
#define WHITE_TRI_ICON  "△"
#define WHITE_CIR_ICON      "○"
/* UNIX */
#elif UNIX
#define BLACK_TRI_ICON  "▲ "
#define BLACK_CIR_ICON      "● "
#define WHITE_TRI_ICON  "△ "
#define WHITE_CIR_ICON      "○ "
#endif

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

///////////////////
// PreAndSet TUI //
///////////////////

#define PREANDSET_OPTION_NUM   3

//#define OPTION_PreAndSet_NUM      3
#define OPTION_PreAndSet_Quit_NUM           31
#define OPTION_PreAndSet_MusicSound_NUM     32
#define OPTION_PreAndSet_NetworkConfig_NUM  33

#define PREANDSET_OPTION_Quit           "<1> Previous Page"
#define PREANDSET_OPTION_MusicSound     "<2> Music & Sound"
#define PREANDSET_OPTION_NetworkConfig  "<3> Network Config"

//////////////////
// AboutChe TUI //
//////////////////

#define ABOUTCHE_OPTION_NUM     1

//define OPTION_AboutChe_NUM        4
#define OPTION_AboutChe_Quit_NUM        41

#define ABOUT_CHESSPLAYER_CONTENT \
    "  `Chessplayer` is the core of this gobang game program, i.e. 'C' in 'PvC'.        " "\n" \
    "  There are six game levels of `Chessplayer` in total: [Drunk], [Low], [Middle],   " "\n" \
    "[High], [Invincible] and [Random]. [Drunk] means that `Chessplayer` will choose its" "\n" \
    "position randomly, just like a drunkard. From [Low] to [Invincible], the game will " "\n" \
    "be more and more difficult to win. [Random] doesn't mean that `Chessplayer` will   " "\n" \
    "choose position randomly. Instead, the core program will choose a level randomly   " "\n" \
    "for you. That's kind of interesting since you don't know the true game level.      " "\n" \
    "  Enjoy yourself! Why not have a try right now.                                     " "\n"

//////////////////
// AboutPro TUI //
//////////////////

#define ABOUTPRO_OPTION_NUM     3

//#define OPTION_AboutPro_NUM       5
#define OPTION_AboutPro_Quit_NUM        51
#define OPTION_AboutPro_Normal_NUM      52
#define OPTION_AboutPro_EasterEgg1_NUM  53
#define OPTION_AboutPro_EasterEgg2_NUM  54

#define ABOUT_PROJECT_CONTENT \
    "  `Gobang.Chessplayer.C` is a small and light project for building a cross-platform" "\n" \
    "gobang game program in console and terminal. As the name suggests, this project is " "\n" \
    "based on C language. Building on different platforms is easy with CMake tool. There" "\n" \
    "is no plan to continue extending this program since it is only a little practice.  " "\n" \
    "In fact, I prefer to call it a cool toy instead a program.                         " "\n" \
    "  Enjoy yourself! Nothing is more beautiful than our life right now.               " "\n"

#define ABOUT_PROJECT_EASTER_EGG_1_CONTENT \
    "  Congratulations! You have found one of the easter eggs in 'About Project' page.  " "\n" \
    "Now you can relax for a while. (I won't tell you that there's another easter egg)  " "\n"

#define ABOUT_PROJECT_EASTER_EGG_2_CONTENT \
    "  The last trace of steam evaporated in the autumn air. The train rounded a corner." "\n" \
    "Harry’s hand was still raised in farewell.                                         " "\n" \
    "  “He’ll be alright,” murmured Ginny.                                              " "\n" \
    "  As Harry looked at her, he lowered his hand absent- mindedly and touched the     " "\n" \
    "lightning scar on his forehead.                                                    " "\n" \
    "  “I know he will.”                                                                " "\n" \
    "  The scar had not pained Harry for nineteen years. All was well.                  " "\n"

///////////////
// Game data //
///////////////

typedef int GAME_RECORD_BOARD[BOARD_SIZE][BOARD_SIZE];

/* iRecordType */
/* GAME_RECORD_BOARD element type */
#define RECORD_BLACK    -1
#define RECORD_WHITE     1

/////////////////////////
// Game prefab configs //
/////////////////////////

typedef struct {
    int mode;
    int order;
    int level;
} GAME_PREFAB_CONFIG;

/* iMode */
#define GPC_MODE_PVP    0
#define GPC_MODE_PVC    1

/* iOrder */
#define GPC_ORDER_PLAYER        10
#define GPC_ORDER_CHESSPLAYER   20

/* iLevel */
/* PvC game difficulty level */
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
/* Oops! Chessplayer is drunk. You win for sure. */
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
#define GPC_LEVEL_DRUNK  -100

#define GPC_LEVEL_LOW      0
#define GPC_LEVEL_MIDDLE   1
#define GPC_LEVEL_HIGH     2

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
/* You lose for sure. Be happy. :-) */
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
#define GPC_LEVEL_INVINCIBLE   100
/*
[米津玄师(よねづけんし) -《Loser / ナンバーナイン》]
アイムアルーザー
我是个loser

どうせだったら远吠えだっていいだろう
所以就算虚张声势也无所谓吧

もう一回もう一回行こうぜ仆らの声
再一次再一次前行吧我们的声音

アイムアルーザー
我是个loser

ずっと前から闻こえてた
很久以前就已经听到

いつかポケットに隠した声が
那不知何时被深藏于口袋之中的声音
*/

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
/* The answer to life, the universe, and everything */
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
#define GPC_LEVEL_RANDOM   42

#define InitGPC(gpc) do { \
    gpc.mode = GPC_MODE_PVP; \
    gpc.order = GPC_ORDER_PLAYER; \
    gpc.level = GPC_LEVEL_DRUNK; \
} while (0)

#endif /* INCLUDE_CHE_DEF_H */
