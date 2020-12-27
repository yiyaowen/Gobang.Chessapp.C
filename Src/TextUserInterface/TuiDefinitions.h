#ifndef TUI_DEFINITIONS_H
#define TUI_DEFINITIONS_H

#define PROMPT "○●○●>> "
#define SELECT_ARROW "○●○●>>"

#define charCountPerAttributeSequence   5

#define BEGIN_ATTR(attr) do { \
    printf(attr); \
} while (0)

#define END_ATTR() do { \
    printf(DEFAULT_ATTR); \
} while (0)

#define NONE_ATTR       "\033[00m"

// Virtual terminal sequences:
// Default attributes don't work well on Windows.
// Use white-foreground with black-background instead.
#ifdef WIN
#define DEFAULT_F_ATTR      "\033[37m"
#define DEFAULT_B_ATTR      "\033[40m"
#elif UNIX
#define DEFAULT_F_ATTR      "\033[39m"
#define DEFAULT_B_ATTR      "\033[49m"
#endif

#define DEFAULT_ATTR    DEFAULT_F_ATTR DEFAULT_B_ATTR

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

#define HIGHLIGHT_TEXT(originText)      "\033[01m" originText "\033[22m"
#define UNDERLINE_TEXT(originText)      "\033[04m" originText "\033[24m"
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

#define HOME_PAGE_DASHBOARD_FRAME_WIDTH     84
#define HOME_PAGE_DASHBOARD_FRAME_HEIGHT    14
#define HOME_PAGE_DASHBOARD_FRAME \
    "//========>>========>>========>>========>>========>>========>>========>>========>>\\\\" "\n" \
    "||  [Gobang News] Last Update: YYYY-MM-dd hh:mm                                   ||" "\n" \
    "||                                                                                ||" "\n" \
    "||  1.                                                                            ||" "\n" \
    "||                                                                                ||" "\n" \
    "||  2.                                                                            ||" "\n" \
    "||                                                                                ||" "\n" \
    "||  3.                                                                            ||" "\n" \
    "||                                                                                ||" "\n" \
    "||  4.                                                                            ||" "\n" \
    "||                                                                                ||" "\n" \
    "||  5.                                                                            ||" "\n" \
    "||                                                                                ||" "\n" \
    "||                                                        <Gobang.Chessplayer.C>  ||" "\n" \
  "\\\\<<========<<========<<========<<========<<========<<========<<========<<========//"

#endif // TUI_DEFINITIONS_H
