#ifndef ABOUT_PRO_PAGE_H
#define ABOUT_PRO_PAGE_H

#include "Route.h"
#include "Page.h"
#include "PageOption.h"

typedef struct type_AboutProPageData {
    int selectedOption;
} AboutProPageData;

PAGE_FUNCTION_TEMPLATE(AboutPro)

Page* getNewAboutProPage();

void printAboutProPageNormalContent();
void printAboutProPageEasterEgg1Content();
void printAboutProPageEasterEgg2Content();

PageOptionID getValidAboutProPageOptionFromUser();

#define ABOUTPRO_PAGE_OPTION_NUM    3

#define ABOUTPRO_PAGE_OPTION_ID_ABOUTPRO    PAGE_ID_ABOUTPRO
#define ABOUTPRO_PAGE_OPTION_ID_PREVIOUS        51
#define ABOUTPRO_PAGE_OPTION_ID_NORMAL          52
#define ABOUTPRO_PAGE_OPTION_ID_EASTEREGG1      53
#define ABOUTPRO_PAGE_OPTION_ID_EASTEREGG2      54

#define ABOUT_PROJECT_NORMAL_CONTENT \
    "   " HIGHLIGHT_TEXT(UNDERLINE_TEXT("`Gobang.Chessplayer.C`")) " is a small and light project for building a cross-platform" "\n" \
    " gobang game program in console and terminal. As the name suggests, this project is " "\n" \
    " based on C language. Building on different platforms is easy with CMake tool.      " "\n\n" \
    "   This program is customizable and can be expand easily. The logic of gobang game  " "\n" \
    " rule and machine algorithm are from " HIGHLIGHT_TEXT(UNDERLINE_TEXT("`Gobang.Core.C`")) " (Includes some simple gobang   " "\n" \
    " game algorithms), which is totally separate from the game program.                 " "\n\n" \
    "   It's easy to use another third party of gobang algorithm to replace the low-level" "\n" \
    " algorithm library used default. By the way, `Gobang.Core.C` also provides a set of " "\n" \
    " interface functions. It's easy to use, if you don't mind. (It's very primary...)   " "\n\n" \
    "   Enjoy yourself! Nothing is more beautiful than our life right now.               " "\n\n" \
    "                  Get source codes: " DARK_GREEN_TEXT(HIGHLIGHT_TEXT(UNDERLINE_TEXT("https://github.com/yiyaowen/Gobang.Chessplayer.C"))) "\n"

#define ABOUT_PROJECT_EASTER_EGG_1_CONTENT \
    "   Congratulations! You have found one of the easter eggs in 'About Project' page.  " "\n" \
    " Now you can relax for a while. (I won't tell you that there's another easter egg)  " "\n"

#define ABOUT_PROJECT_EASTER_EGG_2_CONTENT \
    "   The last trace of steam evaporated in the autumn air. The train rounded a corner." "\n" \
    " Harry’s hand was still raised in farewell.                                         " "\n" \
    "   “He’ll be alright,” murmured Ginny.                                              " "\n" \
    "   As Harry looked at her, he lowered his hand absentmindedly and touched the       " "\n" \
    " lightning scar on his forehead.                                                    " "\n" \
    "   “I know he will.”                                                                " "\n" \
    "   The scar had not pained Harry for nineteen years. All was well.                  " "\n"

#endif // ABOUT_PRO_PAGE_H